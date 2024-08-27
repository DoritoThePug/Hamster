//
// Created by Jaden on 26/08/2024.
//

#ifndef PHYSICS_H
#define PHYSICS_H

#include <box2d/box2d.h>
#include <entt/entity/entity.hpp>
#include <glm/glm.hpp>

namespace Hamster {


class Physics {
public:
    static void Init();

    static void CreateBody(b2BodyType bodyType, entt::entity& entity, entt::registry& registry);

    inline static constexpr float s_PixelsPerMeter = 100.0f;

    static void Simulate();
private:
    static void InitBox2dWorld();

    inline static b2WorldId m_WorldId;

    inline static float m_TimeStep = 1.0f / 60.0f;
    inline static int m_SubStepCount = 4;
};

} // Hamster

#endif //PHYSICS_H
