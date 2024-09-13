//
// Created by Jaden on 03/09/2024.
//

#include "AssetBrowser.h"

#include "Utils/AssetManager.h"
#include <tinyfiledialogs.h>

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

  for (const auto &[uuid, script] : Hamster::AssetManager::GetScriptMap()) {
    std::string buttonLabel =
        script->GetName() + "##" + boost::uuids::to_string(uuid.GetUUID());

    ImGui::Button(buttonLabel.c_str());
  }

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Import Asset")) {
        char const *filterPattern = {"*.png"};
        const char *path = tinyfd_openFileDialog(
            "Select asset", "", 1, &filterPattern, "PNG Files", 0);
        std::string pathStr = path;

        Hamster::UUID uuid;

        Hamster::AssetManager::AddTexture(pathStr);
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
