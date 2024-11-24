//
// Created by Jaden on 26/08/2024.
//

#include "HamsterPCH.h"

#include "Physics.h"

#include "Core/Components.h"
#include "Core/Scene.h"

namespace Hamster {


  bool Physics::IsColliding(const Transform& bodyA, const Transform& bodyB) {
    if ( bodyA.position.x + bodyA.size.x < bodyB.position.x ||
        bodyA.position.y + bodyA.size.y < bodyB.position.y ||
        bodyB.position.x + bodyB.size.x < bodyA.position.x ||
        bodyB.position.y + bodyB.size.y < bodyA.position.y
    ) {
      return false;
    }

  return true;
}

   bool Physics::ResolveCollision(Transform& bodyA, Rigidbody& rbA, Transform& bodyB, Rigidbody& rbB) {
    if (IsColliding(bodyA, bodyB)) {
      glm::vec2 maxA{bodyA.position.x + bodyA.size.x, bodyA.position.y + bodyA.size.y};
      glm::vec2 maxB{bodyB.position.x + bodyB.size.x, bodyB.position.y + bodyB.size.y};

      float overlapX = std::min(maxA.x, maxB.x)- std::max(bodyA.position.x, bodyB.position.x);
      float overlapY = std::min(maxA.y, maxB.y)- std::max(bodyA.position.y, bodyB.position.y);

      if (overlapX < overlapY) {
        // Resolve horizontally

        if (rbA.isStatic) {
          if (bodyA.position.x < bodyB.position.x) {
            bodyB.position.x += overlapX;
          } else {
            bodyB.position.x -= overlapX;
          }
        } else if (rbB.isStatic) {
          if (bodyA.position.x < bodyB.position.x) {
            bodyA.position.x -= overlapX;
          } else {
            bodyA.position.x += overlapX;
          }
        } else {
          if (bodyA.position.x < bodyB.position.x) {
            bodyA.position.x -= overlapX/2;
            bodyB.position.x += overlapX/2;
          } else {
            bodyA.position.x += overlapX/2;
            bodyB.position.x -= overlapX/2;
          }
        }
      }

      else {
        // Resolve vertically

        if (rbA.isStatic) {
          if (bodyA.position.y < bodyB.position.y) {
            bodyB.position.y += overlapY;
          } else {
            bodyB.position.y -= overlapY;
          }
        } else if (rbB.isStatic) {
          if (bodyA.position.y < bodyB.position.y) {
            bodyA.position.y -= overlapY;
          } else {
            bodyA.position.y += overlapY;
          }
        } else {
          if (bodyA.position.y < bodyB.position.y) {
            bodyA.position.y -= overlapY/2;
            bodyB.position.y += overlapY/2;
          } else {
            bodyA.position.y += overlapY/2;
            bodyB.position.y -= overlapY/2;
          }
        }
      }

      return true;
    }

    return false;
  }
} // namespace Hamster
