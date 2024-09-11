#pragma once

#include <memory>

// #include "Core/Scene.h"
#include "Core/UUID.h"
// #include "Core/Components.h"

namespace Hamster {
class Scene;
struct Transform;
// struct ID;
struct Behaviour;

class HamsterBehaviour {
public:
  HamsterBehaviour(UUID entityUUID);

  virtual void OnUpdate() {}

private:
  UUID m_UUID;
  // std::shared_ptr<Scene> m_Scene;

  Transform *m_Transform = nullptr;
};
} // namespace Hamster
