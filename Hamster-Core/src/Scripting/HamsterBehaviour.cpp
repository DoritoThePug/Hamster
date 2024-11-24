#include "HamsterPCH.h"

#include "HamsterBehaviour.h"

#include "Core/Application.h"
#include <box2d/box2d.h>

namespace Hamster {
HamsterBehaviour::HamsterBehaviour(UUID entityUUID,
                                   std::shared_ptr<Scene> scene,
                                   Application *app)
    : m_UUID(entityUUID), m_Scene(std::move(scene)), m_App(app) {
  m_Transform = &m_Scene->GetEntityComponent<Transform>(m_UUID);

  if (m_Scene->EntityHasComponent<Rigidbody>(m_UUID)) {
    m_Rigidbody = &m_Scene->GetEntityComponent<Rigidbody>(m_UUID);
  }

  app->GetEventDispatcher()->Subscribe(
      KeyPressed, FORWARD_CALLBACK_FUNCTION(HamsterBehaviour::OnKeyPressed,
                                            KeyPressedEvent));

  app->GetEventDispatcher()->Subscribe(
      KeyReleased, FORWARD_CALLBACK_FUNCTION(HamsterBehaviour::OnKeyReleased,
                                             KeyReleasedEvent));

  // Application::GetApplicationInstance().GetEventDispatcher();
}

void HamsterBehaviour::SetVelocity(glm::vec2 &vec) {
  std::cout << "setting velocity" << std::endl;

  m_Scene->SetBodyVelocity(m_Rigidbody->id, vec);
}

void HamsterBehaviour::OnKeyPressed(KeyPressedEvent &e) {
  m_KeyPressed = e.GetKeyPressed();

  // std::cout << m_KeyPressed << std::endl;
}

void HamsterBehaviour::OnKeyReleased(KeyReleasedEvent &e) {

  if (e.GetKeyReleased() == m_KeyPressed) {
    m_KeyPressed = NOT_PRESSED;
  }

  m_KeyReleased = e.GetKeyReleased();
}

void HamsterBehaviour::Log(LogType type, std::string message) {
  m_Scene->GetClientLogger()->Log(type, message);
}
} // namespace Hamster
