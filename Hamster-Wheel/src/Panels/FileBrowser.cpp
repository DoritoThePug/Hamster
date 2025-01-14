//
// Created by Jaden on 02/09/2024.
//

#include "FileBrowser.h"

#include <filesystem>

#include <glad/glad.h>

#include <Core/Project.h>

FileBrowser::FileBrowser(std::shared_ptr<Hamster::Scene> scene)
    : Panel(std::move(scene), true) {

  m_FolderIcon = std::make_unique<Hamster::Texture>(
      Hamster::Application::GetExecutablePath() +
      "/../share/Hamster-Wheel/Resources/Icons/folder.png");

  m_FileIcon = std::make_unique<Hamster::Texture>(
      Hamster::Application::GetExecutablePath() +
      "/../share/Hamster-Wheel/Resources/Icons/file.png");
}

void FileBrowser::Render() {
  if (!ImGui::Begin("File Browser", &m_WindowOpen)) {
    ImGui::End();
    return;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // std::cout <<
  // Hamster::Project::GetCurrentProject()->GetConfig().ProjectDirectory <<
  // std::endl;

  std::filesystem::path projectDir =
      Hamster::Project::GetCurrentProject()->GetConfig().ProjectDirectory;

  float browserWidth = ImGui::GetContentRegionAvail().x;
  float columnNum = (int)(browserWidth / (m_IconSize + m_Padding));

  if (columnNum < 1) {
    columnNum = 1;
  }

  ImGui::Columns(columnNum, 0, false);

  for (auto &directory : std::filesystem::directory_iterator(projectDir)) {
    std::string dirPath = directory.path().string();

    std::string relativePath =
        std::filesystem::relative(dirPath, projectDir).string();

    // ImGui::Button(relativePath.c_str());

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0.0f, 0.0f});

    if (directory.is_directory()) {
      ImGui::ImageButton(relativePath.c_str(),
                         (ImTextureID)(intptr_t)m_FolderIcon->GetTextureId(),
                         {64.0f, 64.0f}, {0, 0}, {1, 1}, {0, 0, 0, 1});

      ImGui::TextWrapped("%s", relativePath.c_str());
    } else {

      ImGui::ImageButton(relativePath.c_str(),
                         (ImTextureID)(intptr_t)m_FileIcon->GetTextureId(),
                         {64.0f, 64.0f}, {0, 0}, {1, 1}, {0, 0, 0, 1});

      ImGui::TextWrapped("%s", directory.path().filename().string().c_str());
    }

    ImGui::PopStyleVar();

    ImGui::NextColumn();

    // std::cout << directory.path().string() << std::endl;
  }

  ImGui::End();
}
