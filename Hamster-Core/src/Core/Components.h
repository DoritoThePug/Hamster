//
// Created by Jaden on 26/08/2024.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <memory>

#include <glm/glm.hpp>

#include "Renderer/Texture.h"

namespace Hamster {

    struct Transform {
        glm::vec2 position;
        float rotation;
        glm::vec2 size;
    };

    struct Sprite {
        std::shared_ptr<Texture> texture;
        glm::vec3 colour;
    };

    struct Name {
        std::string name;
    };

} // Hamster

#endif //COMPONENTS_H
