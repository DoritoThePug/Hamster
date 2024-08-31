//
// Created by Jaden on 31/08/2024.
//

#include "Project.h"

#include <filesystem>
#include <utility>

namespace Hamster {
    Project::Project(ProjectConfig config) {
        std::filesystem::create_directory(config.ProjectDirectory);
    }


    bool Project::New(const ProjectConfig &config) {
        if (std::filesystem::exists(config.ProjectDirectory) &&
            std::filesystem::is_directory(config.ProjectDirectory)) {
            std::runtime_error("Project directory already exists");

            return false;
        }

        s_ActiveProject = std::make_unique<Project>(config);

        return true;
    }
} // Hamster
