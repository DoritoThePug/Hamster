//
// Created by Jaden on 28/08/2024.
//

#include "Entity.h"

#include "Application.h"

namespace Hamster {
    Entity::Entity() {
        m_Scene = Application::GetApplicationInstance().GetActiveScene();
        m_UUID = m_Scene->CreateEntity();
        m_Scene->AddEntityComponent<Name>(m_UUID, "Entity");
    }
} // Hamster