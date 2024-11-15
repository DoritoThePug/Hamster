//
// Created by Jaden on 31/08/2024.
//

#ifndef APPLICATIONEVENTS_H
#define APPLICATIONEVENTS_H

#include "Core/Base.h"
#include "Core/Scene.h"
#include "Event.h"

namespace Hamster {
class Scene;

class ActiveSceneChangedEvent : public Event {
public:
  explicit ActiveSceneChangedEvent(std::shared_ptr<Scene> scene)
      : m_ActiveScene(std::move(scene)) {};

  [[nodiscard]] std::shared_ptr<Scene> GetActiveScene() {
    return m_ActiveScene;
  }

  BIND_EVENT_TYPE(ActiveSceneChanged);

private:
  std::shared_ptr<Scene> m_ActiveScene;
};

class ProjectOpenedEvent : public Event {
public:
  explicit ProjectOpenedEvent(std::filesystem::path path) : m_Path(path) {};

  [[nodiscard]] std::filesystem::path GetPath() { return m_Path; }

  BIND_EVENT_TYPE(ProjectOpened);

private:
  std::filesystem::path m_Path;
};

class SceneCreatedEvent : public Event {
public:
  SceneCreatedEvent(std::shared_ptr<Scene> scene) : m_Scene(scene) {};

  std::shared_ptr<Scene> GetScene() { return m_Scene; }

  BIND_EVENT_TYPE(SceneCreated);

private:
  std::shared_ptr<Scene> m_Scene;
};
} // namespace Hamster

#endif // APPLICATIONEVENTS_H
