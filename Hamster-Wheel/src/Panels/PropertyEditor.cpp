//
// Created by Jaden on 24/08/2024.
//

#include "PropertyEditor.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void PropertyEditor::Render() {
    if (!ImGui::Begin("Property Editor", &m_WindowOpen) || Hamster::UUID::IsNil(m_SelectedEntity)) {
        ImGui::End();
        return;
    }

    ImGui::SeparatorText("Transform");

    ImGui::PushItemWidth(80);
    ImGui::Text("Position");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor(230, 57, 70));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) ImColor(216, 77, 89));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor(220, 40, 52));

    ImGui::Button("X##P1", ImVec2(20, 20));

    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    ImGui::InputFloat("##X##P2", &m_Transform->position.x);


    ImGui::SameLine();


    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor(81, 152, 114));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) ImColor(97, 193, 142));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor(50, 145, 95));

    ImGui::Button("Y##P1", ImVec2(20, 20));

    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    ImGui::InputFloat("##Y##P2", &m_Transform->position.y);


    ImGui::Text("Scale");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor(230, 57, 70));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) ImColor(216, 77, 89));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor(220, 40, 52));

    ImGui::Button("X##S1", ImVec2(20, 20));

    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    ImGui::InputFloat("##X##S2", &m_Transform->size.x);


    ImGui::SameLine();


    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor(81, 152, 114));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) ImColor(97, 193, 142));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor(50, 145, 95));

    ImGui::Button("Y##S1", ImVec2(20, 20));

    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    ImGui::InputFloat("##Y##S2", &m_Transform->size.y);


    ImGui::Text("Rotation");
    ImGui::SameLine();

    ImGui::InputFloat("##X#R1", &m_Transform->rotation);


    if (ImGui::Button("Add Component")) {
        ImGui::OpenPopup("Add Component");
    }

    if (ImGui::BeginPopup("Add Component")) {
        ImGui::SeparatorText("Components");

        ImGui::Selectable("Rigidbody");

        if (ImGui::Selectable("Sprite")) {
            // m_Scene->AddEntityComponent<Hamster::Sprite>(m_SelectedEntity, "mario",
            //                                              Hamster::AssetManager::GetTexture("mario"),
            //                                              glm::vec3(1.0f, 1.0f, 1.0f)
            // );
        }

        ImGui::EndPopup();
    }


    ImGui::End();
}

void PropertyEditor::SetSelectedEntity(Hamster::UUID uuid) {
    m_SelectedEntity = uuid;

    if (!Hamster::UUID::IsNil(uuid)) {
        m_Transform = &m_Scene->GetEntityComponent<Hamster::Transform>(uuid);
    }
}

