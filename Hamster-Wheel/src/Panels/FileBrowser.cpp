//
// Created by Jaden on 02/09/2024.
//

#include "FileBrowser.h"

#include <filesystem>

#include "Core/Project.h"

void FileBrowser::Render() {
    if (!ImGui::Begin("File Browser", &m_WindowOpen)) {
        ImGui::End();
        return;
    }

    // std::cout << Hamster::Project::GetCurrentProject()->GetConfig().ProjectDirectory << std::endl;

    std::filesystem::path projectDir = Hamster::Project::GetCurrentProject()->GetConfig().ProjectDirectory;

    for (auto &directory: std::filesystem::directory_iterator(projectDir)) {
        std::string dirPath = directory.path().string();

        std::string relativePath = std::filesystem::relative(dirPath, projectDir).string();


        ImGui::Button(relativePath.c_str());

        // std::cout << directory.path().string() << std::endl;
    }

    ImGui::End();
}
