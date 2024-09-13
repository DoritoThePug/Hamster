//
// Created by Jaden on 26/08/2024.
//

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
  b2CreatePolygonShape(bodyId, &bodyShapeDef, &bodyPolygon);

  scene->AddEntityComponent<Rigidbody>(entityUUID, bodyId);
}

void Physics::Simulate(const b2WorldId &worldId) {
  b2World_Step(worldId, m_TimeStep, m_SubStepCount);
}

void Physics::SetTransform(const b2BodyId &bodyId, Transform &transform) {
  b2Body_SetTransform(bodyId,
                      (b2Vec2){transform.position.x / s_PixelsPerMeter,
                               transform.position.y / s_PixelsPerMeter},
                      b2MakeRot(glm::radians(transform.rotation)));
}

} // namespace Hamster
