//
// Created by Jaden on 26/08/2024.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <memory>

#include <glm/glm.hpp>
#include <box2d/box2d.h>

#include "Renderer/Texture.h"
#include "UUID.h"

namespace Hamster {
    enum ComponentID {
        Transform_ID = 1,
        Sprite_ID = 2,
        Name_ID = 3,
        Rigidbody_ID = 4,
        ID_ID = 5
    };

    struct Transform {
        glm::vec2 position = glm::vec2(0.0f);
        float rotation = 0.0f;
        glm::vec2 size = glm::vec2(10.0f);
    };

    struct Sprite {
        std::string textureName;
        std::shared_ptr<Texture> texture;
        glm::vec3 colour = glm::vec3(1.0f);
    };

    struct Name {
        std::string name = "Entity";
    };

    struct Rigidbody {
        b2BodyId id;
    };

    struct ID {
        UUID uuid;
    };
} // Hamster

#endif //COMPONENTS_H
