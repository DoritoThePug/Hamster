//
// Created by Jaden on 28/08/2024.
//

#include "Scene.h"

#include <utility>

#include "Physics/Physics.h"
#include "Renderer/Renderer.h"
#include "Application.h"
#include "SceneSerialiser.h"

namespace Hamster {
    UUID Scene::CreateEntity() {
        auto entity = m_Registry.create();

        UUID uuid;

        m_Registry.emplace<ID>(entity, uuid);
        m_Entities[uuid] = entity;

        return uuid;
    }

    void Scene::CreateEntityWithUUID(UUID uuid) {
        auto entity = m_Registry.create();

        m_Registry.emplace<ID>(entity, uuid);
        m_Entities[uuid] = entity;
    }


    void Scene::DestroyEntity(UUID entityUUID) {
        m_Registry.destroy(m_Entities[entityUUID]);
        m_Entities.erase(entityUUID);
    }


    // template<typename T>
    // T Scene::GetEntityComponent(UUID uuid) {
    //     return m_Registry.get<T>(uuid);
    // }
    //
    // template<typename T, typename... Args>
    // void Scene::AddEntityComponent(UUID entityUUID, Args &&... args) {
    //     m_Registry.emplace<T>(m_Entities[entityUUID], std::forward<Args>(args)...);
    // }

    void Scene::OnUpdate() {
        if (!m_IsSimulationPaused) {
            Physics::Simulate(m_WorldId);

            auto view = m_Registry.view<Transform, Rigidbody>();

            view.each([this](auto &transform, auto &rb) {
                b2Transform physicsTransform = b2Body_GetTransform(rb.id);
                // std::cout << pos.x << ", " << pos.y << std::endl;

                transform.position = glm::vec2(physicsTransform.p.x * Physics::s_PixelsPerMeter,
                                               physicsTransform.p.y * Physics::s_PixelsPerMeter);

                transform.rotation = glm::degrees(b2Rot_GetAngle(physicsTransform.q));
            });
        }
    }

    void Scene::OnRender(bool renderFlat) {
        auto view = m_Registry.view<Sprite, Transform>();

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if (m_IsRunning) {
            if (!renderFlat) {
                view.each([](auto &sprite, auto &transform) {
                    Renderer::DrawSprite(*sprite.texture, transform.position, transform.size, transform.rotation,
                                         sprite.colour);
                });
            } else {
                // render all sprites as a unique flat colour which can be used to identify to their id

                // std::cout << "hi" << std::endl;

                view.each([](auto entity, auto &sprite, auto &transform) {
                    Renderer::DrawFlat(transform.position, transform.size, transform.rotation,
                                       Application::IdToColour(entt::to_integral(entity)));
                });
            }
        }
    }

    void Scene::SaveScene(std::shared_ptr<Scene> scene) {
        std::cout << "Saving scene" << std::endl;

        SceneSerialiser serialiser(std::move(scene));

        std::ofstream out("hi.hs", std::ios::binary);

        serialiser.Serialise(out);

        out.close();
    }
} // Hamster
