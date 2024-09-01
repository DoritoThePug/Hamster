//
// Created by Jaden on 31/08/2024.
//

#ifndef APPLICATIONEVENTS_H
#define APPLICATIONEVENTS_H

#include "Event.h"
#include "Core/Base.h"
#include "Core/Scene.h"

namespace Hamster {
    class ActiveSceneChangedEvent : public Event {
    public:
        explicit ActiveSceneChangedEvent(std::shared_ptr<Scene> scene) : m_ActiveScene(std::move(scene)) {
        };

        [[nodiscard]] std::shared_ptr<Scene> GetActiveScene() { return m_ActiveScene; }

        BIND_EVENT_TYPE(ActiveSceneChanged);

    private:
        std::shared_ptr<Scene> m_ActiveScene;
    };

    class ProjectOpenedEvent : public Event {
    public:
        BIND_EVENT_TYPE(ProjectOpened);
    };
}


#endif //APPLICATIONEVENTS_H
