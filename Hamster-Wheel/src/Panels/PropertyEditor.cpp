// Created by Jaden on 24/08/2024.
//

#include "PropertyEditor.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include <Scripting/Scripting.h>

#include <box2d/box2d.h>
// #include "Scripting/Scripting.h"

void PropertyEditor::Render() {
  if (!ImGui::Begin("Property Editor", &m_WindowOpen) ||
      Hamster::UUID::IsNil(m_SelectedEntity)) {
    ImGui::End();
    return;
  }

  if (m_Transform != nullptr) {
    ImGui::SeparatorText("Transform");

    ImGui::PushItemWidth(80);
    ImGui::Text("Position");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(230, 57, 70));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(216, 77, 89));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(220, 40, 52));

    ImGui::Button("X##P1", ImVec2(20, 20));

    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    ImGui::InputFloat("##X##P2", &m_Transform->position.x);

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(81, 152, 114));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                          (ImVec4)ImColor(97, 193, 142));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(50, 145, 95));

    ImGui::Button("Y##P1", ImVec2(20, 20));

    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    ImGui::InputFloat("##Y##P2", &m_Transform->position.y);

    ImGui::Text("Scale");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(230, 57, 70));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(216, 77, 89));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(220, 40, 52));

    ImGui::Button("X##S1", ImVec2(20, 20));

    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    ImGui::InputFloat("##X##S2", &m_Transform->size.x);

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(81, 152, 114));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                          (ImVec4)ImColor(97, 193, 142));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(50, 145, 95));

    ImGui::Button("Y##S1", ImVec2(20, 20));

    ImGui::PopStyleColor(3);
    ImGui::SameLine();

    ImGui::InputFloat("##Y##S2", &m_Transform->size.y);

    ImGui::Text("Rotation");
    ImGui::SameLine();

    ImGui::InputFloat("##X#R1", &m_Transform->rotation);
  }

  if (m_Sprite != nullptr) {
    ImGui::SeparatorText("Sprite");

    ImGui::PushItemWidth(80);

    if (m_Sprite->texture != nullptr) {
      ImGui::Text("Current Sprite: ");
      ImGui::SameLine();
      ImGui::Text(m_Sprite->texture->GetName().c_str());
    }

    if (ImGui::Button("Select Sprite")) {
      ImGui::OpenPopup("Select Asset");
    }

    if (ImGui::BeginPopup("Select Asset")) {
      for (const auto &[uuid, texture] :
           Hamster::AssetManager::GetTextureMap()) {
        if (ImGui::Selectable(texture->GetName().c_str())) {
          m_Sprite->texture = texture;
        }
      }

      ImGui::EndPopup();
    }
  }

  if (m_Behaviour != nullptr) {
    ImGui::SeparatorText("Scripts");

    ImGui::PushItemWidth(80);

    for (auto &script : m_Behaviour->scripts) {
      ImGui::Text(script->GetScriptPath().string().c_str());
    }
  }

  if (m_Rigidbody != nullptr) {
    ImGui::SeparatorText("Rigidbody");
  }

  // if (m_Script != nullptr) {
  //   ImGui::SeparatorText("Script");
  //
  //   ImGui::Text(m_Script->scriptPath.c_str());
  // }

  if (ImGui::Button("Add Component")) {
    ImGui::OpenPopup("Add Component");
  }

  if (ImGui::BeginPopup("Add Component")) {
    ImGui::SeparatorText("Components");

    if (!m_Scene->EntityHasComponent<Hamster::Rigidbody>(m_SelectedEntity)) {
      if (ImGui::Selectable("Rigidbody")) {
        Hamster::Physics::CreateBody(m_SelectedEntity, m_Scene, b2_dynamicBody);
      }
    }

    if (!m_Scene->EntityHasComponent<Hamster::Sprite>(m_SelectedEntity)) {
      if (ImGui::Selectable("Sprite")) {
        m_Scene->AddEntityComponent<Hamster::Sprite>(m_SelectedEntity);
      }
    }

    // if (!m_Scene->EntityHasComponent<Hamster::Script>(m_SelectedEntity)) {
    if (ImGui::Selectable(("Script"))) {
      Hamster::Scripting::AddScriptComponent(m_SelectedEntity, m_Scene);
    }

    // }

    ImGui::EndPopup();
  }

  ImGui::End();
}

void PropertyEditor::SetSelectedEntity(Hamster::UUID uuid) {
  m_SelectedEntity = uuid;

  if (!Hamster::UUID::IsNil(m_SelectedEntity)) {
    if (m_Scene->EntityHasComponent<Hamster::Transform>(m_SelectedEntity)) {
      m_Transform =
          &m_Scene->GetEntityComponent<Hamster::Transform>(m_SelectedEntity);
    } else {
      m_Transform = nullptr;
    }

    if (m_Scene->EntityHasComponent<Hamster::Sprite>(m_SelectedEntity)) {
      m_Sprite =
          &m_Scene->GetEntityComponent<Hamster::Sprite>(m_SelectedEntity);
    } else {
      m_Sprite = nullptr;
    }

    // if (m_Scene->EntityHasComponent<Hamster::Script>(m_SelectedEntity)) {
    //   m_Script =
    //   &m_Scene->GetEntityComponent<Hamster::Script>(m_SelectedEntity);
    // }

    if (m_Scene->EntityHasComponent<Hamster::Behaviour>(m_SelectedEntity)) {
      m_Behaviour =
          &m_Scene->GetEntityComponent<Hamster::Behaviour>(m_SelectedEntity);
    } else {
      m_Behaviour = nullptr;
    }

    if (m_Scene->EntityHasComponent<Hamster::Rigidbody>(m_SelectedEntity)) {
      m_Rigidbody =
          &m_Scene->GetEntityComponent<Hamster::Rigidbody>(m_SelectedEntity);
    } else {
      m_Rigidbody = nullptr;
    }
  }
}
