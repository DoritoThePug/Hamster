//
// Created by Jaden on 31/08/2024.
//

#ifndef PROJECT_H
#define PROJECT_H
#include <string>
#include <filesystem>

namespace Hamster {
    struct ProjectConfig {
        std::string Name;
        std::filesystem::path ProjectDirectory;
    };

    class Project {
    public:
        Project(ProjectConfig config);

        static bool New(const ProjectConfig &config);

    private:
        ProjectConfig m_Config;

        inline static std::unique_ptr<Project> s_ActiveProject;
    };
} // Hamster

#endif //PROJECT_H
