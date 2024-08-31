//
// Created by Jaden on 31/08/2024.
//

#include "Project.h"

namespace Hamster {
    Project::Project(const std::string &name, const std::filesystem::path &projectDirectory) : m_Config(name, projectDirectory){
    }
} // Hamster
