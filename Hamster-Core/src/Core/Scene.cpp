//
// Created by Jaden on 28/08/2024.
//

#include "Scene.h"

#include <utility>

#include "Application.h"
#include "Physics/Physics.h"
#include "Renderer/Renderer.h"
#include "SceneSerialiser.h"

#include "Scripting/HamsterBehaviour.h"
#include "Scripting/Scripting.h"

namespace Hamster {
  Scene::Scene() {
    Application::GetApplicationInstance().GetEventDispatcher()->Subscribe(
      SceneCreated,
      FORWARD_CALLBACK_FUNCTION(Scene::OnSceneCreated, SceneCreatedEvent));

    std::string sceneName = m_Name;
    std::replace(sceneName.begin(), sceneName.end(), ' ', '_');

    m_Path = std::filesystem::path("Scenes") /
             std::filesystem::path(sceneName + "_" + m_UUID.GetUUIDString() +
                                   ".scene");
  }

  UUID Scene::CreateEntity() {
    auto entity = m_Registry.create();

    UUID uuid;

    std::cout << "Created " << uuid.GetUUID() << std::endl;

    m_Registry.emplace<ID>(entity, uuid);
    m_Entities[uuid] = entity;

    AddEntityComponent<Transform>(uuid);
    AddEntityComponent<Name>(uuid);

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
  //     m_Registry.emplace<T>(m_Entities[entityUUID],
  //     std::forward<Args>(args)...);
  // }

  void Scene::OnUpdate() {
    if (!m_IsSimulationPaused) {
      // auto scripts = m_Registry.view<Script>();

      // scripts.each(
      // [](auto &script) { script.scriptModule.attr("OnUpdate")(333); });

      // Physics::Simulate(m_WorldId);
      //
      // auto view = m_Registry.view<Transform, Rigidbody>();
      //
      // view.each([this](auto &transform, auto &rb) {
      //   b2Transform physicsTransform = b2Body_GetTransform(rb.id);
      //   // std::cout << pos.x << ", " << pos.y << std::endl;
      //
      //   transform.position =
      //       glm::vec2(physicsTransform.p.x * Physics::s_PixelsPerMeter,
      //                 physicsTransform.p.y * Physics::s_PixelsPerMeter);
      //
      //   transform.rotation = glm::degrees(b2Rot_GetAngle(physicsTransform.q));
      // });
      //

      //   auto behaviours = m_Registry.view<Behaviour>();
      //
      //   behaviours.each([](auto &behaviour) {
      //     for (auto &script : behaviour.scripts) {
      //       for (auto &objects : script.GetPyObjects()) {
      //         objects.attr("OnUpdate")();
      //       }
      //     }
      //   });
      //
      auto view = m_Registry.view<Behaviour>();

      view.each([](auto &behaviour) {
        for (auto &obj: behaviour.pyObjects) {
          obj.attr("OnUpdate")();
        }
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
          if (sprite.texture != nullptr) {
            Renderer::DrawSprite(*sprite.texture, transform.position,
                                 transform.size, transform.rotation,
                                 sprite.colour);
          }
        });
      } else {
        // render all sprites as a unique flat colour which can be used to
        // identify to their id

        // std::cout << "hi" << std::endl;

        view.each([](auto entity, auto &sprite, auto &transform) {
          if (sprite.texture != nullptr) {
            Renderer::DrawFlat(
              transform.position, transform.size, transform.rotation,
              Application::IdToColour(entt::to_integral(entity)));
          }
        });
      }
    }
  }

  void Scene::SaveScene(std::shared_ptr<Scene> scene) {
    std::cout << "Saving scene" << std::endl;

    SceneSerialiser serialiser(scene);

    std::cout << scene->GetPath() << std::endl;

    std::ofstream out(scene->GetPath(), std::ios::binary);

    serialiser.Serialise(out);

    out.close();
  }

  void Scene::OnSceneCreated(SceneCreatedEvent &e) { SaveScene(e.GetScene()); }

  void Scene::SetUUID(const UUID &uuid) {
    m_UUID = uuid;

    std::cout << m_UUID.GetUUID() << std::endl;

    std::string sceneName = m_Name;

    std::replace(sceneName.begin(), sceneName.end(), ' ', '_');

    m_Path = std::filesystem::path("Scenes") /
             std::filesystem::path(sceneName + "_" + m_UUID.GetUUIDString() +
                                   ".scene");
  }

  void Scene::RunSceneSimulation() {
    Scripting::InitInterpreter();

    auto reloadView = m_Registry.view<Behaviour>();

    reloadView.each([](auto &behaviour) {
      for (auto &script: behaviour.scripts) {
        script->ReloadScript();
      }
    });

    m_IsSimulationPaused = false;

    auto view = m_Registry.view<ID, Behaviour>();

    view.each([](auto &ID, auto &behaviour) {
      for (auto &script: behaviour.scripts) {
        for (auto &obj: script->GetPyObjects()) {
          // HamsterBehaviour *s = pybind11::cast<HamsterBehaviour *>(obj());

          // obj(ID.uuid);

          // pybind11::object instance = obj(ID.uuid);
          // HamsterBehaviour s = obj(ID.uuid).cast<HamsterBehaviour>();
          behaviour.pyObjects.push_back(obj(
            ID.uuid, Application::GetApplicationInstance().GetActiveScene()));
          // obj();
          // pybind11::object class_type = obj.get_type();

          // pybind11::str class_name = class_type.attr("__name__");

          // std::cout << class_name.cast<std::string>() << std::endl;

          // std::cout << ID.uuid.GetUUIDString() << std::endl;
        }
      }
    });
  }

  void Scene::PauseSceneSimulation() {
    m_IsSimulationPaused = true;

    auto view = m_Registry.view<Behaviour>();

    view.each([](auto &behaviour) { behaviour.pyObjects.clear(); });

    Scripting::FinaliseInterpreter();
  }
} // namespace Hamster
