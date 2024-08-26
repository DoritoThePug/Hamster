//
// Created by Jaden on 25/08/2024.
//

#include "Hierarchy.h"

Hierarchy::Hierarchy( Hamster::Application& app) : m_App(app) {
}

entt::entity Hierarchy::GetSelectedEntity() const {
    return m_SelectedEntity;
}

void Hierarchy::SetSelectedEntity(const entt::entity entity) {
    m_SelectedEntity = entity;
}

void Hierarchy::Render() {
    if(!ImGui::Begin("Hierarchy", &m_WindowOpen)) {
        ImGui::End();
        return;
    }

    const auto view = m_App.GetRegistry().view<Hamster::Name>();

    view.each([&](auto entity, auto& name) {
        ImGui::PushID(entt::to_integral(entity));

        if (entity == m_SelectedEntity) {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        }



        if (ImGui::TreeNode(name.name.c_str())) {


            ImGui::TreePop();
        }

        if (ImGui::IsItemClicked()) {
            SetSelectedEntity(entity);
            std::cout << name.name << std::endl;
        }

        ImGui::PopID();
    });

    ImGui::End();
}
