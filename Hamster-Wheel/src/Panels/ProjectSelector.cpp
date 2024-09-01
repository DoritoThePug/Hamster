//
// Created by Jaden on 01/09/2024.
//

#include "ProjectSelector.h"

//
// Created by Jaden on 31/08/2024.
//

#include "ProjectSelector.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

void ProjectSelector::Render() {
    if (!ImGui::Begin("Project Selector", &m_WindowOpen)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Project File Path");
    ImGui::SameLine();

    if (ImGui::Button("Select Project")) {
        HWND owner = glfwGetWin32Window(Hamster::Application::GetApplicationInstance().GetWindow());

        m_ProjectFilePath = OpenWindowsFileDialog(owner);

        m_NoPathSelected = false;
    }

    if (ImGui::Button("Open Project")) {
        if (m_ProjectFilePath.empty()) {
            m_NoPathSelected = true;
        } else {
            Hamster::Project::Open(m_ProjectFilePath);
            m_ProjectFilePath.clear();

            ClosePanel();
        }
    }

    if (m_NoPathSelected) {
        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor(230, 57, 70));
        ImGui::Text("You must choose a project to open!");
        ImGui::PopStyleColor();
    }

    ImGui::End();
}

std::string ProjectSelector::OpenWindowsFileDialog(HWND owner) {
    OPENFILENAME ofn;
    char szFile[MAX_PATH];


    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = owner;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);

    ofn.lpstrFilter = "Hamster Project File\0*.hamproj\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;


    if (GetOpenFileName(&ofn) == TRUE) {
        return std::string(ofn.lpstrFile);
    }

    return "";
}
