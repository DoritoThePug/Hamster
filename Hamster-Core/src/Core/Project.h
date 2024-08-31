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
        Project(const std::string &name, const std::filesystem::path &projectDirectory);

    private:
        ProjectConfig m_Config;
    };
} // Hamster

#endif //PROJECT_H
