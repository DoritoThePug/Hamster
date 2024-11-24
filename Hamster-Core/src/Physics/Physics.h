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

namespace Hamster {
struct ID;
class Scene;

class Physics {
public:
  static bool IsColliding(const Transform& bodyA, const Transform& bodyB);
  static bool ResolveCollision(Transform& bodyA, Rigidbody& rbA, Transform& bodyB, Rigidbody& rbB);
private:
};
} // namespace Hamster

#endif // PHYSICS_H
