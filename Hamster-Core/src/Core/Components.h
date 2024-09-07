//
// Created by Jaden on 26/08/2024.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <memory>

#include <box2d/box2d.h>
#include <glm/glm.hpp>

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
  Sprite(std::shared_ptr<Texture> tex, glm::vec3 col)
      : texture(tex), colour(col) {};
  Sprite(glm::vec3 col) : colour(col) {};
  Sprite() {};

  std::shared_ptr<Texture> texture = nullptr;
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
} // namespace Hamster

#endif // COMPONENTS_H
