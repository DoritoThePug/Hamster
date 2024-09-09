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
  Entity(UUID uuid, std::shared_ptr<Scene> scene, entt::entity entityHandle)
      : m_UUID(uuid), m_Scene(std::move(scene)),
        m_EntityHandle(entityHandle) {};

  // Entity()

  virtual void OnCreate() {};

  virtual void OnUpdate(float deltaTime) {};

  virtual void OnDestroyed() {};

  entt::entity &GetEntityHandle() { return m_entityHandle; }

  UUID &GetUUID() { return m_UUID; }
  UUID &SetUUID(UUID uuid) { m_UUID = uuid; }

  std::shared_ptr<Scene> GetScene() { return m_Scene; }
  void SetScene(std::shared_ptr<Scene> scene) { m_Scene = scene; }

  template <typename T> bool HasComponent() {
    m_Scene->EntityHasComponent<T>(m_UUID);
  }

  template <typename T, typename... Args>
  void AddComponent(T component, Args &&...args) {
    m_Scene->AddEntityComponent<T>(m_UUID, std::forward<Args>(args));
  }

  template <typename T> T &GetComponent() {
    return m_Scene->GetEntityComponent<T>(m_UUID);
  }

private:
  UUID m_UUID;
  std::shared_ptr<Scene> m_Scene;
  entt::entity m_EntityHandle;
};
} // namespace Hamster

#endif // ENTITY_H
