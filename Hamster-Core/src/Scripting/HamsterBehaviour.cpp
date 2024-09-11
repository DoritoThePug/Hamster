#include "HamsterBehaviour.h"

#include "Core/Application.h"

namespace Hamster {
  HamsterBehaviour::HamsterBehaviour(UUID entityUUID) : m_UUID(entityUUID) {
    // m_Transform = &m_Scene->GetEntityComponent<Transform>(m_UUID);
    //


    // m_Transform = &Application::GetApplicationInstance()
    //                    .GetActiveScene()
    //                    ->GetEntityComponent<Transform>(m_UUID);
  }
} // namespace Hamster
