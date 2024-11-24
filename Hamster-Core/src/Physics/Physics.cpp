//
// Created by Jaden on 26/08/2024.
//

#include "HamsterPCH.h"

#include "Physics.h"

#include "Core/Components.h"
#include "Core/Scene.h"

namespace Hamster {
b2WorldId Physics::InitBox2dWorld() {
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = (b2Vec2){0.0f, 1.0f};

  return b2CreateWorld(&worldDef);
}

void Physics::CreateBody(const UUID &entityUUID, std::shared_ptr<Scene> scene,
                         b2BodyType bodyType) {
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = bodyType;

  Transform &entityTransform = scene->GetEntityComponent<Transform>(entityUUID);

  bodyDef.position = (b2Vec2){entityTransform.position.x / s_PixelsPerMeter,
                              entityTransform.position.y / s_PixelsPerMeter};
  bodyDef.rotation = b2MakeRot(glm::radians(entityTransform.rotation));

  b2BodyId bodyId = b2CreateBody(scene->GetWorldId(), &bodyDef);

  b2Polygon bodyPolygon =
      b2MakeBox((entityTransform.size.x / s_PixelsPerMeter) / 2,
                (entityTransform.size.y / s_PixelsPerMeter) / 2);

  b2ShapeDef bodyShapeDef = b2DefaultShapeDef();
  b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &bodyShapeDef, &bodyPolygon);

  m_ShapeToEntity.emplace(shapeId, entityUUID);

  if (scene->EntityHasComponent<Rigidbody>(entityUUID)) {
    Rigidbody &entityRb = scene->GetEntityComponent<Rigidbody>(entityUUID);

    entityRb.id = bodyId;
    entityRb.shapeId = shapeId;

    entityRb.dynamic = (bodyType == b2_dynamicBody) ? true : false;
  } else {
    scene->AddEntityComponent<Rigidbody>(
        entityUUID, bodyId, shapeId,
        (bodyType == b2_dynamicBody) ? true : false);
  }
}

void Physics::ChangeBodyType(const UUID &entityUUID,
                             std::shared_ptr<Scene> scene,
                             b2BodyType bodyType) {
  Rigidbody &rb = scene->GetEntityComponent<Rigidbody>(entityUUID);

  b2Body_SetType(rb.id, bodyType);
}

void Physics::Simulate(const b2WorldId &worldId) {
  b2World_Step(worldId, m_TimeStep, m_SubStepCount);

  b2ContactEvents contactEvents = b2World_GetContactEvents(worldId);

  for (int i = 0; i < contactEvents.beginCount; i++) {
    b2ContactBeginTouchEvent e = contactEvents.beginEvents[i];

    std::cout << Physics::GetEntityFromShape(e.shapeIdA).GetUUIDString()
              << " collided with "
              << Physics::GetEntityFromShape(e.shapeIdB).GetUUIDString()
              << std::endl;
  }
}

void Physics::SetTransform(const b2BodyId &bodyId, Transform &transform) {
  b2Body_SetTransform(bodyId,
                      (b2Vec2){transform.position.x / s_PixelsPerMeter,
                               transform.position.y / s_PixelsPerMeter},
                      b2MakeRot(glm::radians(transform.rotation)));
}

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
} // namespace Hamster
