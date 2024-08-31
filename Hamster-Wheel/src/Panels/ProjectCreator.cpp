//
// Created by Jaden on 31/08/2024.
//

#include "ProjectCreator.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

void ProjectCreator::Render() {
    if (!ImGui::Begin("Project Creator", &m_WindowOpen)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Project Name");
    ImGui::SameLine();
    ImGui::InputText("##textInput#", m_ProjectNameInput, IM_ARRAYSIZE(m_ProjectNameInput));

    ImGui::Text("Project Directory");
    ImGui::SameLine();

    if (ImGui::Button("Select Directory")) {
        HWND owner = glfwGetWin32Window(Hamster::Application::GetApplicationInstance().GetWindow());

        m_ProjectConfig.ProjectDirectory = OpenWindowsFileDialog(owner);
    }

    if (ImGui::Button("Create Project")) {
        if (m_ProjectConfig.ProjectDirectory.empty()) {
            HWND owner = glfwGetWin32Window(Hamster::Application::GetApplicationInstance().GetWindow());

            m_ProjectConfig.ProjectDirectory = OpenWindowsFileDialog(owner);
        } else {
            CreateProject();

            m_ProjectConfig = Hamster::ProjectConfig();
        }

        ImGui::End();
    }
}

std::string ProjectCreator::OpenWindowsFileDialog(HWND owner) {
    BROWSEINFO bi = {0};
    bi.lpszTitle = "Select Directory";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.hwndOwner = owner;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != 0) {
        char path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path)) {
            // Free the PIDL allocated by SHBrowseForFolder
            CoTaskMemFree(pidl);
            return std::string(path);
        }
    }
    return "";
}


void CreateProject() {
    
}
