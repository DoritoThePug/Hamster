//
// Created by Jaden on 31/08/2024.
//

#ifndef PROJECT_H
#define PROJECT_H
#include <string>
#include <filesystem>

#include "Scene.h"

namespace Hamster {
    struct ProjectConfig {
        std::string Name;
        std::filesystem::path ProjectDirectory;
        std::filesystem::path StartScenePath;
    };

    class Project {
    public:
        Project(ProjectConfig config);

        static bool New(const ProjectConfig &config);

        static void SaveCurrentProject();

        void SetStartScene(std::shared_ptr<Scene> scene);

        [[nodiscard]] const ProjectConfig &GetConfig() const;

    private:
        ProjectConfig m_Config;

        inline static std::unique_ptr<Project> s_ActiveProject;

        std::shared_ptr<Scene> m_StartScene = nullptr;
    };
} // Hamster

#endif //PROJECT_H
