//
// Created by Jaden on 30/08/2024.
//

#include "MenuBar.h"

#include <imgui.h>
#include <iostream>

#include "Core/SceneSerialiser.h"

void MenuBar::Render() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                Hamster::Scene::SaveScene(m_Scene);
                // std::cout << "Saving scene" << std::endl;
                //
                // Hamster::SceneSerialiser serialiser(m_Scene);
                //
                // std::ofstream out("hi.hs", std::ios::binary);
                //
                // serialiser.Serialise(out);
                //
                // out.close();
            }

            if (ImGui::MenuItem("New Project")) {
                m_ProjectCreator->OpenPanel();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (m_ProjectCreator->IsPanelOpen()) {
        m_ProjectCreator->Render();
    }
}
