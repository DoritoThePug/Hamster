//
// Created by Jaden on 21/08/2024.
//

#include "PropertyEditor.h"

#include "imgui.h"

namespace Hamster {
    void PropertyEditor::Render() {
        if(!ImGui::Begin("Property Editor", &m_WindowOpen)) {
            ImGui::End();
            return;
        }

        ImGui::SeparatorText("Transform");

        ImGui::PushItemWidth(80);
        ImGui::Text("Position"); ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(230, 57, 70));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(216, 77, 89));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(220, 40, 52));

        ImGui::Button("X", ImVec2(20, 20));

        ImGui::PopStyleColor(3); ImGui::SameLine();

        ImGui::InputFloat("##X", &m_f); ImGui::SameLine();


        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(81, 152, 114));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(97, 193, 142));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(50, 145, 95));

        ImGui::Button("Y", ImVec2(20, 20));

        ImGui::PopStyleColor(3); ImGui::SameLine();

        ImGui::InputFloat("##Y", &m_f);


        ImGui::PopItemWidth();

        ImGui::End();
    }
} // Hamster