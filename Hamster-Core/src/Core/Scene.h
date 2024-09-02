//
// Created by Jaden on 28/08/2024.
//

#ifndef SCENE_H
#define SCENE_H

#include <entt/entt.hpp>
#include <box2d/box2d.h>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>
#include <filesystem>

#include <boost/uuid/uuid_io.hpp>

#include "Components.h"

#include "UUID.h"
#include "Events/ApplicationEvents.h"
#include "Events/WindowEvents.h"
#include "Physics/Physics.h"

namespace Hamster {
    class SceneCreatedEvent;

    class Scene {
    public:
        Scene();

        UUID CreateEntity();

        void CreateEntityWithUUID(UUID uuid);

        void DestroyEntity(UUID entityUUID);

        entt::entity &GetEntity(UUID entityUUID) { return m_Entities[entityUUID]; }
        UUID GetEntityUUID(entt::entity entity) { return m_Registry.get<ID>(entity).uuid; }

        entt::registry &GetRegistry() { return m_Registry; }

        // template <typename T>
        // T GetEntityComponent(UUID uuid);
        //
        // template <typename T, typename... Args>
        // void AddEntityComponent(UUID entityUUID, Args&&... args);

        template<typename T>
        T &GetEntityComponent(UUID uuid) {
            return m_Registry.get<T>(m_Entities[uuid]);
        }

        template<typename T, typename... Args>
        void AddEntityComponent(UUID entityUUID, Args &&... args) {
            m_Registry.emplace<T>(m_Entities[entityUUID], std::forward<Args>(args)...);
        }


        void OnUpdate();

        void OnRender(bool renderFlat);

        bool IsSceneRunning() const { return m_IsRunning; }
        bool IsSceneSimulationPaused() const { return m_IsSimulationPaused; }

        void RunScene() { m_IsRunning = true; }
        void RunSceneSimulation() { m_IsSimulationPaused = false; }

        void PauseScene() { m_IsRunning = false; }
        void PauseSceneSimulation() { m_IsSimulationPaused = true; }

        b2WorldId GetWorldId() { return m_WorldId; }

        UUID GetUUID() const { return m_UUID; }

        void SetUUID(const UUID uuid) {
            m_UUID = uuid;
        }

        uint32_t GetEntityCount() const { return static_cast<uint32_t>(m_Entities.size()); }
        const std::unordered_map<UUID, entt::entity> &GetEntityMap() { return m_Entities; }

        static void SaveScene(std::shared_ptr<Scene> scene);

        std::string &GetName() { return m_Name; }

        std::filesystem::path &GetPath() { return m_Path; }

        void OnSceneCreated(SceneCreatedEvent &e);

    private:
        bool m_IsRunning = false;
        bool m_IsSimulationPaused = true;

        entt::registry m_Registry;
        std::unordered_map<UUID, entt::entity> m_Entities;

        b2WorldId m_WorldId = Physics::InitBox2dWorld();

        UUID m_UUID;
        std::string m_Name = "Untitled Scene";
        std::filesystem::path m_Path;
    };
} // Hamster

#endif //SCENE_H
