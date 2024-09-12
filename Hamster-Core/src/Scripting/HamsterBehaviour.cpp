#include "HamsterBehaviour.h"

#include "Core/Application.h"

namespace Hamster {
HamsterBehaviour::HamsterBehaviour(UUID entityUUID,
                                   std::shared_ptr<Scene> scene)
    : m_UUID(entityUUID), m_Scene(std::move(scene)) {
  m_Transform = &m_Scene->GetEntityComponent<Transform>(m_UUID);
  //

  // if ( Application::GetApplicationInstance()) {
  // std::cout << "asd" << std::endl;
  // }
  //    Application::GetApplicationInstance().GetActiveScene();

  // Application::GetApplicationInstance();

  // m_Transform = &Application::GetApplicationInstance()
  // .GetActiveScene()
  // ->GetEntityComponent<Transform>(m_UUID);
}
} // namespace Hamster
