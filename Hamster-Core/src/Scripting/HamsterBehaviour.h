#pragma once

#include "Core/Components.h"
#include "Core/Scene.h"
#include "Events/Event.h"
#include "Events/InputEvents.h"
#include "Utils/InputManager.h"

namespace Hamster {
class Scene;
struct Transform;
// struct ID;
struct Behaviour;
class Application;

class HamsterBehaviour {
public:
  HamsterBehaviour(UUID entityUUID, std::shared_ptr<Scene> scene,
                   Application *app);

  virtual void OnCreate() {}
  virtual void OnUpdate(float deltaTime) {}

  const Transform &GetTransform() { return *m_Transform; }

  void SetTransform(const Transform &transform) {
    m_Transform->position = transform.position;
    m_Transform->rotation = transform.rotation;
    m_Transform->size = transform.size;
  }

  const KeyCodes &GetKeyPressed() { return m_KeyPressed; }
  const KeyCodes &GetKeyReleased() { return m_KeyPressed; }

  void OnKeyPressed(KeyPressedEvent &e);
  void OnKeyReleased(KeyReleasedEvent &e);

  void ResetInput() { m_KeyReleased = NOT_PRESSED; }

private:
  UUID m_UUID;
  std::shared_ptr<Scene> m_Scene;
  Transform t;
  Application *m_App;

  Transform *m_Transform = nullptr;
  KeyCodes m_KeyPressed = NOT_PRESSED;
  KeyCodes m_KeyReleased = NOT_PRESSED;
};
} // namespace Hamster
