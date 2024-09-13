//
// Created by Jaden on 26/08/2024.
//

#ifndef PHYSICS_H
#define PHYSICS_H

#include <memory>

#include <box2d/box2d.h>
#include <entt/entity/entity.hpp>
#include <glm/glm.hpp>

#include "Core/Components.h"
#include "Core/UUID.h"

// #include "Core/Scene.h"

namespace Hamster {
struct ID;
class Scene;

class Physics {
public:
  static b2WorldId InitBox2dWorld();

  static void CreateBody(const UUID &entityUUID, std::shared_ptr<Scene> scene,
                         b2BodyType bodyType);

  inline static constexpr float s_PixelsPerMeter = 100.0f;

  static void Simulate(const b2WorldId &worldId);

  static void SetTransform(const b2BodyId &bodyId, Transform &transform);

private:
  inline static float m_TimeStep = 1.0f / 60.0f;
  inline static int m_SubStepCount = 4;
};
} // namespace Hamster

#endif // PHYSICS_H
