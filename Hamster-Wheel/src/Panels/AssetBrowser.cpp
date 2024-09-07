//
// Created by Jaden on 03/09/2024.
//

#include "AssetBrowser.h"

// #include <windows.h>
// #include <shlobj.h>

#include "tinyfiledialogs.h"
#include "Utils/AssetManager.h"

void AssetBrowser::Render() {
    if (!ImGui::Begin("AssetBrowser", &m_WindowOpen, ImGuiWindowFlags_MenuBar)) {
        ImGui::End();
        return;
    }

    for (const auto &[uuid, texture]: Hamster::AssetManager::GetTextureMap()) {
        std::string buttonLabel = texture->GetName() + "##" + boost::uuids::to_string(uuid.GetUUID());

        ImGui::Button(buttonLabel.c_str());
    }

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Add Asset")) {
                // HWND owner = glfwGetWin32Window(Hamster::Application::GetApplicationInstance().GetWindow());
                //
                // std::string chosenPath = OpenWindowsFileDialog(owner);

                char const* filterPattern = {"*.png"};
                const char* path = tinyfd_openFileDialog("Select asset", "", 1, &filterPattern, "PNG Files", 0);
                std::string pathStr = path;

                Hamster::UUID uuid;

                Hamster::AssetManager::AddTexture(pathStr);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

// std::string AssetBrowser::OpenWindowsFileDialog(HWND owner) {
//     OPENFILENAME ofn;
//     char szFile[MAX_PATH];
//
//
//     ZeroMemory(&ofn, sizeof(ofn));
//     ofn.lStructSize = sizeof(ofn);
//     ofn.hwndOwner = owner;
//     ofn.lpstrFile = szFile;
//     ofn.lpstrFile[0] = '\0';
//     ofn.nMaxFile = sizeof(szFile);
//
//     ofn.lpstrFilter = "Sprite File\0*.png\0";
//     ofn.nFilterIndex = 1;
//     ofn.lpstrFileTitle = NULL;
//     ofn.nMaxFileTitle = 0;
//     ofn.lpstrInitialDir = NULL;
//     ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;
//
//
//     if (GetOpenFileName(&ofn) == TRUE) {
//         return std::string(ofn.lpstrFile);
//     }
//
//     return "";
// }
