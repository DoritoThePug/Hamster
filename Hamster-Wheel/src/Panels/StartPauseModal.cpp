//
// Created by Jaden on 27/08/2024.
//

#include "StartPauseModal.h"


StartPauseModal::StartPauseModal(Hamster::Application& app) : m_App(app) {

}

void StartPauseModal::Render() {
    ImGui::Begin("StartPauseModal", &m_WindowOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize );

        if (ImGui::Button("Start")) {
            m_App.ResumeSimulation();
        }


        ImGui::SameLine();


        if(ImGui::Button("Pause")) {
            m_App.PauseSimulation();
        }

    ImGui::End();

}
