//
// Created by Jaden on 26/08/2024.
//

#ifndef PHYSICS_H
#define PHYSICS_H

#include <unordered_map>

#include <box2d/box2d.h>
#include <entt/entity/entity.hpp>
#include <glm/glm.hpp>

#include "Core/Components.h"

// #include "Core/Scene.h"

namespace std {
template <> struct hash<b2ShapeId> {
  std::size_t operator()(const b2ShapeId &id) const {
    std::size_t h1 = std::hash<int32_t>()(id.index1);
    std::size_t h2 = std::hash<uint16_t>()(id.world0);
    std::size_t h3 = std::hash<uint16_t>()(id.revision);

    // Combine the hashes
    return h1 ^ (h2 << 1) ^ (h3 << 2);
  }
};

template <> struct equal_to<b2ShapeId> {
  bool operator()(const b2ShapeId &lhs, const b2ShapeId &rhs) const {
    return (lhs.index1 == rhs.index1) && (lhs.world0 == rhs.world0) &&
           (lhs.revision == rhs.revision);
  }
};
} // namespace std

namespace Hamster {
struct ID;
class Scene;

class Physics {
public:
  static b2WorldId InitBox2dWorld();

  static void CreateBody(const UUID &entityUUID, std::shared_ptr<Scene> scene,
                         b2BodyType bodyType);

  static void ChangeBodyType(const UUID &entityUUID,
                             std::shared_ptr<Scene> scene, b2BodyType bodyType);

  inline static constexpr float s_PixelsPerMeter = 100.0f;

  static void Simulate(const b2WorldId &worldId);

  static void SetTransform(const b2BodyId &bodyId, Transform &transform);

  static UUID GetEntityFromShape(b2ShapeId id) {
    return m_ShapeToEntity.at(id);
  }

  static bool IsColliding(const Transform& bodyA, const Transform& bodyB);

private:
  inline static float m_TimeStep = 1.0f / 60.0f;
  inline static int m_SubStepCount = 4;
  inline static std::unordered_map<b2ShapeId, UUID> m_ShapeToEntity;
};
} // namespace Hamster

#endif // PHYSICS_H
