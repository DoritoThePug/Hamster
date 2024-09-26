//
// Created by Jaden on 28/08/2024.
//

#ifndef SCENE_H
#define SCENE_H

#include <box2d/box2d.h>
#include <entt/entt.hpp>

#include <boost/container_hash/hash.hpp>

#include <boost/uuid/uuid_io.hpp>

#include "Components.h"

#include "Events/ApplicationEvents.h"
#include "Events/WindowEvents.h"
#include "Log.h"
#include "Physics/Physics.h"

namespace Hamster {
class SceneCreatedEvent;
// class HamsterBehaviour;
// class HamsterScript;
// struct ID;
// class UUID
//

class Scene {
public:
  Scene();

  UUID CreateEntity();

  void CreateEntityWithUUID(UUID uuid);

  void DestroyEntity(UUID entityUUID);

  entt::entity &GetEntity(UUID entityUUID) { return m_Entities[entityUUID]; }

  UUID GetEntityUUID(entt::entity entity) {
    return m_Registry.get<ID>(entity).uuid;
  }

  entt::registry &GetRegistry() { return m_Registry; }

  // template <typename T>
  // T GetEntityComponent(UUID uuid);
  //
  // template <typename T, typename... Args>
  // void AddEntityComponent(UUID entityUUID, Args&&... args);

  template <typename T> T &GetEntityComponent(UUID uuid) {
    return m_Registry.get<T>(m_Entities[uuid]);
  }

  template <typename T, typename... Args>
  void AddEntityComponent(UUID entityUUID, Args &&...args) {
    m_Registry.emplace<T>(m_Entities[entityUUID], std::forward<Args>(args)...);
  }

  template <typename T> bool EntityHasComponent(UUID entityUUID) {
    return m_Registry.all_of<T>(m_Entities[entityUUID]);
  }

  void OnUpdate();

  void OnRender(bool renderFlat);

  bool IsSceneRunning() const { return m_IsRunning; }
  bool IsSceneSimulationPaused() const { return m_IsSimulationPaused; }

  void RunScene() { m_IsRunning = true; }
  void RunSceneSimulation();

  void PauseScene() { m_IsRunning = false; }
  void PauseSceneSimulation();

  b2WorldId GetWorldId() { return m_WorldId; }

  UUID GetUUID() const { return m_UUID; }

  void SetUUID(const UUID &uuid);

  uint32_t GetEntityCount() const {
    return static_cast<uint32_t>(m_Entities.size());
  }

  const std::unordered_map<UUID, entt::entity> &GetEntityMap() {
    return m_Entities;
  }

  static void SaveScene(std::shared_ptr<Scene> scene);

  std::string &GetName() { return m_Name; }

  std::filesystem::path &GetPath() { return m_Path; }

  void OnSceneCreated(SceneCreatedEvent &e);

  std::shared_ptr<Logger> GetClientLogger() { return m_ClientLogger; }

private:
  bool m_IsRunning = false;
  bool m_IsSimulationPaused = true;

  entt::registry m_Registry;
  std::unordered_map<UUID, entt::entity> m_Entities;

  b2WorldId m_WorldId = Physics::InitBox2dWorld();

  UUID m_UUID;
  std::string m_Name = "Untitled Scene";
  std::filesystem::path m_Path;

  float m_DeltaTime = 0.0f;
  float m_LastFrame = 0.0f;

  std::shared_ptr<Logger> m_ClientLogger;
};
} // namespace Hamster

#define HAMSTER_LOG(type, message)                                             \
  Hamster::Application::GetApplicationInstance()                               \
      .GetActiveScene()                                                        \
      ->GetClientLogger()                                                      \
      ->Log(type, message);

#endif // SCENE_H
