#include "HamsterPCH.h"

#include "HamsterBehaviour.h"

#include "Core/Application.h"
#include <box2d/box2d.h>

#include "Events/SceneEvents.h"

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

  app->GetEventDispatcher()->Subscribe(
      Collision,
      FORWARD_CALLBACK_FUNCTION(HamsterBehaviour::OnCollision, CollisionEvent));

  // Application::GetApplicationInstance().GetEventDispatcher();
}

void HamsterBehaviour::OnKeyPressed(KeyPressedEvent &e) {
  m_KeyPressed = e.GetKeyPressed();
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

void HamsterBehaviour::CrossScriptExecute(std::string &uuid,
                                          const char *funcName) {
  auto &behaviour = m_Scene->GetEntityComponent<Behaviour>(UUID(uuid));

  for (auto &obj : behaviour.pyObjects) {
    if (pybind11::hasattr(obj, funcName)) {
      obj.attr(funcName)();
      break;
    }
  }
}

void HamsterBehaviour::AddCollisionEntity(const std::string &uuid) {
  m_CollisionEntities.insert(uuid);

  m_Colliding = true;
}

void HamsterBehaviour::EmptyCollisionEntity() {
  m_CollisionEntities.clear();
  m_Colliding = false;
}

void HamsterBehaviour::OnCollision(CollisionEvent &e) {
  if (e.GetUUIDA().GetUUID() == m_UUID.GetUUID()) {
    AddCollisionEntity(e.GetUUIDB().GetUUIDString());
  } else if (e.GetUUIDB().GetUUID() == m_UUID.GetUUID()) {
    AddCollisionEntity(e.GetUUIDA().GetUUIDString());
  }
}

// void HamsterBehaviour::RegisterEvent(pybind11::object &obj) {
//   m_Scene->GetEventDispatcher()->RegisterEvent(obj);
// }

void HamsterBehaviour::Subscribe(const pybind11::object &event,
                                 pybind11::function fn) {
  m_Scene->GetEventDispatcher()->Subscribe(event, fn);
  // pybind11::hash(event);
}

void HamsterBehaviour::Post(const pybind11::object &event) {
  m_Scene->GetEventDispatcher()->Post(event);
}

} // namespace Hamster
