//
// Created by Jaden on 26/08/2024.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <memory>

#include <box2d/box2d.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <pybind11/pybind11.h>

#include "Renderer/Texture.h"
#include "Scripting/HamsterScript.h"
#include "UUID.h"

namespace Hamster {
// class HamsterScript;
// class Scne;
// class Physics;

enum ComponentID {
  Transform_ID = 1,
  Sprite_ID = 2,
  Name_ID = 3,
  Rigidbody_ID = 4,
  ID_ID = 5,
  Behaviour_ID
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

struct Behaviour {
  // std::vector<std::shared_ptr<HamsterScript> > scripts;
  std::unordered_map<UUID, std::shared_ptr<HamsterScript>> scripts;
  std::vector<pybind11::object> pyObjects;
};
} // namespace Hamster

#endif // COMPONENTS_H
