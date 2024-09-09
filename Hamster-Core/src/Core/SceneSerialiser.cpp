//
// Created by Jaden on 29/08/2024.
//

#include "SceneSerialiser.h"

#include <boost/uuid/uuid_io.hpp>
#include <entt/entt.hpp>
#include <iostream>
#include <string>
#include <utility>

#include "Utils/AssetManager.h"

namespace Hamster {
SceneSerialiser::SceneSerialiser(std::shared_ptr<Scene> scene)
    : m_Scene(std::move(scene)) {}

void SceneSerialiser::Serialise(std::ostream &out) {
  boost::uuids::uuid uuidValue = m_Scene->GetUUID().GetUUID();

  out.write(reinterpret_cast<const char *>(&uuidValue), uuidValue.size());

  uint32_t entityCount = m_Scene->GetEntityCount();

  std::cout << "Entity count: " << entityCount << std::endl;

  out.write(reinterpret_cast<const char *>(&entityCount), sizeof(entityCount));

  for (auto const &[uuid, entity] : m_Scene->GetEntityMap()) {
    SerialiseEntity(out, entity, uuid);
  }
}

void SceneSerialiser::Deserialise(std::istream &in) {
  boost::uuids::uuid boostUUID;
  in.read(reinterpret_cast<char *>(&boostUUID), boostUUID.size());

  std::cout << "Boost UUID: " << boostUUID << std::endl;

  UUID uuid(boostUUID);

  m_Scene->SetUUID(uuid);

  uint32_t count;
  in.read(reinterpret_cast<char *>(&count), sizeof(count));

  std::cout << "Entity count: " << count << std::endl;

  for (uint32_t i = 0; i < count; i++) {
    DeserialiseEntity(in);
  }
}

void SerialiseVec2(std::ostream &out, const glm::vec2 &v) {
  out.write(reinterpret_cast<const char *>(&v.x), sizeof(v.x));
  out.write(reinterpret_cast<const char *>(&v.y), sizeof(v.y));
}

glm::vec2 DeserialiseVec2(std::istream &in) {
  glm::vec2 v;

  in.read(reinterpret_cast<char *>(&v.x), sizeof(v.x));
  in.read(reinterpret_cast<char *>(&v.y), sizeof(v.y));

  return v;
}

void SerialiseVec3(std::ostream &out, const glm::vec3 &v) {
  out.write(reinterpret_cast<const char *>(&v.x), sizeof(v.x));
  out.write(reinterpret_cast<const char *>(&v.y), sizeof(v.y));
  out.write(reinterpret_cast<const char *>(&v.z), sizeof(v.z));
}

glm::vec3 DeserialiseVec3(std::istream &in) {
  glm::vec3 v;

  in.read(reinterpret_cast<char *>(&v.x), sizeof(v.x));
  in.read(reinterpret_cast<char *>(&v.y), sizeof(v.y));
  in.read(reinterpret_cast<char *>(&v.z), sizeof(v.z));

  return v;
}

// void SceneSerialiser::SerialiseEntity(std::ostream &out,
//                                       entt::entity const &entity,
//                                       UUID const &entity_uuid) {
//   std::cout << "Serialising entity with UUID: " << entity_uuid.GetUUID()
//             << std::endl;
//
//   UUID::Serialise(out, entity_uuid);
//
//   if (m_Scene->GetRegistry().all_of<Transform>(entity)) {
//     int id = static_cast<int>(Transform_ID);
//
//     out.write(reinterpret_cast<const char *>(&id), sizeof(id));
//
//     Transform &transform = m_Scene->GetRegistry().get<Transform>(entity);
//
//     SerialiseVec2(out, transform.position);
//
//     out.write(reinterpret_cast<const char *>(&transform.rotation),
//               sizeof(transform.rotation));
//
//     SerialiseVec2(out, transform.size);
//   }
//
//   if (m_Scene->GetRegistry().all_of<Sprite>(entity)) {
//     int id = static_cast<int>(Sprite_ID);
//
//     out.write(reinterpret_cast<const char *>(&id), sizeof(id));
//
//     Sprite &sprite = m_Scene->GetRegistry().get<Sprite>(entity);
//
//     if (sprite.texture != nullptr) {
//       UUID::Serialise(out, sprite.texture->GetUUID());
//     } else {
//       UUID::Serialise(out, UUID::GetNil());
//     }
//
//     SerialiseVec3(out, sprite.colour);
//   }
//
//   if (m_Scene->GetRegistry().all_of<Name>(entity)) {
//     int id = static_cast<int>(Name_ID);
//     out.write(reinterpret_cast<const char *>(&id), sizeof(id));
//
//     Name &name = m_Scene->GetRegistry().get<Name>(entity);
//
//     std::size_t nameLength = name.name.size();
//     out.write(reinterpret_cast<const char *>(&nameLength),
//     sizeof(nameLength)); out.write(reinterpret_cast<const char
//     *>(name.name.data()), nameLength);
//   }
//
// if (m_Scene->GetRegistry().all_of<Rigidbody>(entity)) {
//     int id = static_cast<int>(Rigidbody_ID);
//     out.write(reinterpret_cast<const char *>(&id), sizeof(id));
//   }
//
//   int endId = -1;
//
//   out.write(reinterpret_cast<const char *>(&endId), sizeof(endId));
// }

void SceneSerialiser::SerialiseEntity(std::ostream &out, Entity const &entity) {
  std::cout << "Serialising entity with UUID: "
            << entity.GetUUID().GetUUIDString() << std::endl;

  UUID::Serialise(out, Entity.GetUUID())'

      if (entity.HasComponent<Transform>()) {
    int id = static_cast<int>(Transform_ID);

    out.write(reinterpret_cast<const char *>(&id), sizeof(id));

    Transform &transform = entity.GetComponent<Transform>();

    SerialiseVec2(out, transform.position);

    out.write(reinterpret_cast<const char *>(&transform.rotation),
              sizeof(transform.rotation));

    SerialiseVec2(out, transform.size);
  }

  if (entity.HasComponent<Sprite>()) {
    int id = static_cast<int>(Sprite_ID);

    out.write(reinterpret_cast<const char *>(&id), sizeof(id));

    Sprite &sprite = entity.HasComponent<Sprite>();

    if (sprite.texture != nullptr) {
      UUID::Serialise(out, sprite.texture->GetUUID());
    } else {
      UUID::Serialise(out, UUID::GetNil());
    }

    SerialiseVec3(out, sprite.colour);
  }

  if (entity.HasComponent<Name>) {
    int id = static_cast<int>(Name_ID);
    out.write(reinterpret_cast<const char *>(&id), sizeof(id));

    Name &name = entity.GetComponent<Name>();

    std::size_t nameLength = name.name.size();
    out.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
    out.write(reinterpret_cast<const char *>(name.name.data()), nameLength);
  }

  if (entity.HasComponent<Rigidbody>) {
    int id = static_cast<int>(Rigidbody_ID);
    out.write(reinterpret_cast<const char *>(&id), sizeof(id));
  }

  int endId = -1;

  out.write(reinterpret_cast<const char *>(&endId), sizeof(endId));
}

Entity SceneSerialiser::DeserialiseEntity(std::istream &in) {
  entity.SetScene(m_Scene);

  std::cout << "Deserialising entity with uuid: " << uuid.GetUUIDString()
            << std::endl;

  // m_Scene->CreateEntityWithUUID(uuid);

  int componentId;

  while (in.read(reinterpret_cast<char *>(&componentId), sizeof(componentId))) {
    std::cout << "Deserialising component id: " << componentId << std::endl;

    switch (componentId) {
    case Transform_ID: {
      glm::vec2 pos = DeserialiseVec2(in);

      float rotation;

      in.read(reinterpret_cast<char *>(&rotation), sizeof(rotation));

      glm::vec2 size = DeserialiseVec2(in);

      std::cout << pos.x << " " << pos.y << " " << rotation << " " << size.x
                << " " << size.y << std::endl;

      m_Scene->AddEntityComponent<Transform>(uuid, pos, rotation, size);

      break;
    }
    case Sprite_ID: {
      UUID textureUUID = UUID::Deserialise(in);

      std::cout << textureUUID.GetUUIDString() << std::endl;

      glm::vec3 colour = DeserialiseVec3(in);

      std::cout << colour.r << " " << colour.g << std::endl;

      std::cout << UUID::IsNil(textureUUID) << std::endl;

      if (!UUID::IsNil(textureUUID)) {
        m_Scene->AddEntityComponent<Sprite>(
            uuid, AssetManager::GetTexture(textureUUID), colour);
      } else {
        m_Scene->AddEntityComponent<Sprite>(uuid, colour);
      }

      break;
    }
    case Name_ID: {
      std::size_t nameLength;
      in.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));

      std::string name(nameLength, '\0');
      in.read(reinterpret_cast<char *>(name.data()), nameLength);

      m_Scene->AddEntityComponent<Name>(uuid, name);

      break;
    }
    case Rigidbody_ID: {
      Physics::CreateBody(m_Scene->GetWorldId(), b2_dynamicBody,
                          m_Scene->GetEntity(uuid), m_Scene->GetRegistry());

      break;
    }
    case -1: {
      return uuid;
    }
    default: {
      std::cout << componentId << std::endl;

      throw std::runtime_error("Unrecognized scene serialisation type");
    }
    }
  }
}
} // namespace Hamster
