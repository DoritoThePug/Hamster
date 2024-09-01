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
        Project(const ProjectConfig &config);

        static bool New(ProjectConfig &config);

        static bool Open(std::filesystem::path projectPath);

        static void SaveCurrentProject();

        void SetStartScene(std::shared_ptr<Scene> scene);

        [[nodiscard]] ProjectConfig &GetConfig();

    private:
        ProjectConfig m_Config;

        inline static std::shared_ptr<Project> s_ActiveProject = nullptr;

        std::shared_ptr<Scene> m_StartScene = nullptr;
    };
} // Hamster

#endif //PROJECT_H
