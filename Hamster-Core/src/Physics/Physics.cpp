//
// Created by Jaden on 26/08/2024.
//

#include "Physics.h"

#include <Core/Components.h>
#include <entt/entity/registry.hpp>


namespace Hamster {
    void Physics::Init() {
        InitBox2dWorld();
    }

    void Physics::InitBox2dWorld() {
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = (b2Vec2){0.0f, 1.0f};

        m_WorldId = b2CreateWorld(&worldDef);
    }

    void Physics::CreateBody(b2BodyType bodyType, entt::entity& entity, entt::registry& registry) {
        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = bodyType;

        Transform entityTransform = registry.get<Transform>(entity);

        bodyDef.position = (b2Vec2){entityTransform.position.x/s_PixelsPerMeter, entityTransform.position.y/s_PixelsPerMeter};

        b2BodyId bodyId = b2CreateBody(m_WorldId, &bodyDef);

        b2Polygon bodyPolygon = b2MakeBox((entityTransform.size.x/s_PixelsPerMeter)/2, (entityTransform.size.y/s_PixelsPerMeter)/2);

        b2ShapeDef bodyShapeDef = b2DefaultShapeDef();
        b2CreatePolygonShape(bodyId, &bodyShapeDef, &bodyPolygon);

        registry.emplace<Rigidbody>(entity, bodyId);
    }

    void Physics::Simulate() {
        b2World_Step(m_WorldId, m_TimeStep, m_SubStepCount);
    }

} // Hamster