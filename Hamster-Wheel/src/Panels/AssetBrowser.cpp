//
// Created by Jaden on 03/09/2024.
//

#include "AssetBrowser.h"

#include "Utils/AssetManager.h"
#include <tinyfiledialogs.h>

#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>

AssetBrowser::AssetBrowser(std::shared_ptr<Hamster::Scene> scene)
    : Hamster::Panel(scene) {

  std::string wheelPath = HAMSTER_WHEEL_SRC_DIR;

  m_PythonIcon = std::make_unique<Hamster::Texture>(
      wheelPath + "/../Resources/Icons/python.png");
};

void AssetBrowser::Render() {
  if (!ImGui::Begin("AssetBrowser", &m_WindowOpen, ImGuiWindowFlags_MenuBar)) {
    ImGui::End();
    return;
  }

  for (const auto &[uuid, texture] : Hamster::AssetManager::GetTextureMap()) {
    std::string buttonLabel =
        texture->GetName() + "##" + boost::uuids::to_string(uuid.GetUUID());

    ImGui::Button(buttonLabel.c_str());
  }

  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0.0f, 0.0f});

  for (const auto &[uuid, script] : Hamster::AssetManager::GetScriptMap()) {
    std::string buttonLabel =
        script->GetName() + "##" + boost::uuids::to_string(uuid.GetUUID());

    ImGui::ImageButton(script->GetName().c_str(),
                       (ImTextureID)(intptr_t)m_PythonIcon->GetTextureId(),
                       {64.0f, 64.0f}, {0, 0}, {1, 1}, {0, 0, 0, 1});
  }

  ImGui::PopStyleVar();

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Import Asset")) {

        char const *filterPattern = {"*.png"};
        const char *path = tinyfd_openFileDialog(
            "Select asset", "", 1, &filterPattern, "PNG Files", 1);

        std::stringstream pathSS(path);
        std::string item;

        while (std::getline(pathSS, item, '|')) {
          Hamster::AssetManager::AddTextureAsync(item);
        }
      }
      if (ImGui::MenuItem("New Script")) {
        Hamster::AssetManager::AddDefaultScript();
      }

      ImGui::EndMenu();
    }

    ImGui::EndMenuBar();
  }

  ImGui::End();
}
