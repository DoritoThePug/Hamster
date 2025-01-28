//
// Created by Jaden on 31/08/2024.
//

#include "HamsterPCH.h"

#include "Project.h"

#include "Application.h"
#include "ProjectSerialiser.h"
#include "SceneSerialiser.h"
#include "Utils/AssetManager.h"

namespace Hamster {
    Project::Project(const ProjectConfig &config) : m_Config(config) {
        std::filesystem::create_directory(config.ProjectDirectory);

        std::filesystem::current_path(config.ProjectDirectory);
    }

    bool Project::New(ProjectConfig &config) {
        if (std::filesystem::exists(config.ProjectDirectory) &&
            std::filesystem::is_directory(config.ProjectDirectory)) {
            std::runtime_error("Project directory already exists");

            return false;
        }

        if (s_ActiveProject != nullptr) {
            Hamster::Project::SaveCurrentProject();
        }

        Application::GetApplicationInstance().StopActiveScene();

        Application::GetApplicationInstance().RemoveAllScenes();

        std::filesystem::create_directory(config.ProjectDirectory);
        std::filesystem::current_path(config.ProjectDirectory);

        std::filesystem::create_directory("Scenes");

        std::shared_ptr<Scene> scene = std::make_shared<Scene>();

        Application::GetApplicationInstance().AddScene(scene);

        std::cout << scene->GetUUID().GetUUID() << std::endl;

        SceneSerialiser sceneSerialiser(scene);

        std::filesystem::path scenePath = config.ProjectDirectory / scene->GetPath();

        std::cout << scenePath << std::endl;

        std::ofstream sceneOut(scenePath, std::ios::binary);
        sceneSerialiser.Serialise(sceneOut);
        sceneOut.close();

        config.StartScenePath = scenePath;

        Application::GetApplicationInstance().SetSceneActive(scene->GetUUID());

        s_ActiveProject = std::make_shared<Project>(config);

        SaveCurrentProject();

        Application::GetApplicationInstance().AddScene(scene);
        Application::GetApplicationInstance().SetSceneActive(scene->GetUUID());

        ProjectOpenedEvent e(config.ProjectDirectory);

        Application::GetApplicationInstance()
                .GetEventDispatcher()
                ->Post<ProjectOpenedEvent>(e);

        return true;
    }

    bool Project::Open(std::filesystem::path projectPath) {
        if (s_ActiveProject != nullptr) {
            Project::SaveCurrentProject();
        }

        Application::GetApplicationInstance().StopActiveScene();

        Application::GetApplicationInstance().RemoveAllScenes();

        std::ifstream projectFile(projectPath, std::ios::binary);

        ProjectConfig config = ProjectSerialiser::Deserialise(projectFile);

        s_ActiveProject = std::make_shared<Project>(config);

        AssetManager::Deserialise(projectFile, config);

        projectFile.close();

        std::shared_ptr<Scene> scene = std::make_shared<Scene>();
        SceneSerialiser sceneSerialiser(scene);
        std::ifstream sceneIn(config.StartScenePath, std::ios::binary);
        sceneSerialiser.Deserialise(sceneIn);
        sceneIn.close();

        s_ActiveProject->SetStartScene(scene);

        Application::GetApplicationInstance().AddScene(scene);

        Application::GetApplicationInstance().SetSceneActive(scene->GetUUID());

        ProjectOpenedEvent e(projectPath);

        Application::GetApplicationInstance()
                .GetEventDispatcher()
                ->Post<ProjectOpenedEvent>(e);

        std::filesystem::current_path(config.ProjectDirectory);

        return true;
    }

    void Project::SaveCurrentProject() {
        if (s_ActiveProject != nullptr) {
            ProjectSerialiser serialiser(s_ActiveProject);

            std::cout << s_ActiveProject->GetConfig().Name << std::endl;

            std::ofstream out(s_ActiveProject->GetConfig().Name + ".hamproj",
                              std::ios::binary);

            serialiser.Serialise(out);

            AssetManager::Serialise(out);

            out.close();
        }
    }

    void Project::SetStartScene(std::shared_ptr<Scene> scene) {
        m_StartScene = std::move(scene);
    }

    ProjectConfig &Project::GetConfig() { return m_Config; }
} // namespace Hamster
