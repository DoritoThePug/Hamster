//
// Created by Jaden on 28/08/2024.
//

#ifndef SCENE_H
#define SCENE_H

#include <entt/entt.hpp>
#include <box2d/box2d.h>
#include <unordered_map>
#include <boost/container_hash/hash.hpp>

#include "Components.h"

#include "UUID.h"
#include "Physics/Physics.h"

namespace Hamster {

class Scene {
public:
    Scene() {};

    UUID CreateEntity();
    void DestroyEntity(UUID entityUUID);

    entt::registry& GetRegistry() {return m_Registry; }

    // template <typename T>
    // T GetEntityComponent(UUID uuid);
    //
    // template <typename T, typename... Args>
    // void AddEntityComponent(UUID entityUUID, Args&&... args);

    template<typename T>
    T GetEntityComponent(UUID uuid) {
        return m_Registry.get<T>(uuid);
    }

    template<typename T, typename... Args>
    void AddEntityComponent(UUID entityUUID, Args &&... args) {
        m_Registry.emplace<T>(m_Entities[entityUUID], std::forward<Args>(args)...);
    }


    void OnUpdate();
    void OnRender(bool renderFlat);

    bool IsSceneRunning() const {return m_IsRunning; }
    bool IsSceneSimulationPaused() const {return m_IsSimulationPaused; }

    void RunScene() {m_IsRunning = true;}
    void RunSceneSimulation() {m_IsSimulationPaused = false;}

    void PauseScene() {m_IsRunning = false;}
    void PauseSceneSimulation() {m_IsSimulationPaused = true;}

    UUID GetUUID() const {return m_UUID; }
private:
    bool m_IsRunning = false;
    bool m_IsSimulationPaused = true;

    entt::registry m_Registry;
    std::unordered_map<UUID, entt::entity> m_Entities;

    b2WorldId m_WorldId = Physics::InitBox2dWorld();

    UUID m_UUID;
};

} // Hamster

#endif //SCENE_H
