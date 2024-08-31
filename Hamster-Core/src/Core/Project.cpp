//
// Created by Jaden on 31/08/2024.
//

#include "Project.h"

#include <filesystem>
#include <fstream>

#include "Application.h"
#include "ProjectSerialiser.h"
#include "SceneSerialiser.h"

namespace Hamster {
    Project::Project(ProjectConfig config) {
        std::filesystem::create_directory(config.ProjectDirectory);

        std::filesystem::current_path(config.ProjectDirectory);
    }


    bool Project::New(const ProjectConfig &config) {
        if (std::filesystem::exists(config.ProjectDirectory) &&
            std::filesystem::is_directory(config.ProjectDirectory)) {
            std::runtime_error("Project directory already exists");

            return false;
        }

        // Hamster::Project::SaveCurrentProject();

        Application::GetApplicationInstance().StopActiveScene();

        Application::GetApplicationInstance().RemoveAllScenes();


        s_ActiveProject = std::make_unique<Project>(config);
        std::filesystem::current_path(config.ProjectDirectory);

        std::shared_ptr<Scene> scene = std::make_shared<Scene>();

        SceneSerialiser sceneSerialiser(scene);

        std::ofstream sceneOut("Scene.hs", std::ios::binary);
        sceneSerialiser.Serialise(sceneOut);

        Application::GetApplicationInstance().AddScene(scene);
        Application::GetApplicationInstance().SetSceneActive(scene->GetUUID());

        return true;
    }

    void Project::SaveCurrentProject() {
        ProjectSerialiser serialiser(std::move(s_ActiveProject));

        std::ofstream out(s_ActiveProject->GetConfig().Name + ".hamproj", std::ios::binary);

        serialiser.Serialise(out);

        out.close();
    }

    void Project::SetStartScene(std::shared_ptr<Scene> scene) {
        m_StartScene = std::move(scene);
    }

    const ProjectConfig &Project::GetConfig() const {
        return m_Config;
    }
} // Hamster
