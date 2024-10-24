//
// Created by Jaden on 31/08/2024.
//

#ifndef SCENEEVENTS_H
#define SCENEEVENTS_H

#include "Event.h"

namespace Hamster {
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
} // namespace Hamster

#endif // SCENEEVENTS_H
