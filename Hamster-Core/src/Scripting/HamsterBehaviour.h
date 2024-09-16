#pragma once

#include "Core/Components.h"
#include "Core/Scene.h"

namespace Hamster {
class Scene;
struct Transform;
// struct ID;
struct Behaviour;

class HamsterBehaviour {
public:
  HamsterBehaviour(UUID entityUUID, std::shared_ptr<Scene> scene);

  virtual void OnUpdate() {}

  const Transform &GetTransform() { return *m_Transform; }

  void SetTransform(const Transform &transform) {
    m_Transform->position = transform.position;
    m_Transform->rotation = transform.rotation;
    m_Transform->size = transform.size;
  }

private:
  UUID m_UUID;
  std::shared_ptr<Scene> m_Scene;
  Transform t;

  Transform *m_Transform = nullptr;
};
} // namespace Hamster
