//
// Created by Jaden on 28/08/2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <entt/entity/entity.hpp>

#include "Entity.h"
#include "Scene.h"
#include "UUID.h"

namespace Hamster {

class Entity {
public:
    Entity();

    virtual void OnCreate() {};
    virtual void OnUpdate(float deltaTime) {};
    virtual void OnDestroyed() {};

private:
    UUID m_UUID;
    std::shared_ptr<Scene> m_Scene;
};

} // Hamster

#endif //ENTITY_H