//
// Created by Jaden on 25/08/2024.
//

#ifndef PANEL_H
#define PANEL_H
#include <memory>
#include <utility>

#include "Core/Application.h"
#include "Core/Scene.h"
#include "Events/Event.h"

namespace Hamster {
    class Panel {
    public:
        Panel(std::shared_ptr<Scene> scene, bool defaultOpen = true) : m_WindowOpen(defaultOpen),
                                                                       m_Scene(std::move(scene)) {
            Application::GetApplicationInstance().GetEventDispatcher()->Subscribe(
                ActiveSceneChanged,
                FORWARD_CALLBACK_FUNCTION(Panel::OnActiveSceneChanged, ActiveSceneChangedEvent));
        };

        Panel(bool defaultOpen) : m_WindowOpen(defaultOpen) {
            Application::GetApplicationInstance().GetEventDispatcher()->Subscribe(
                ActiveSceneChanged,
                FORWARD_CALLBACK_FUNCTION(Panel::OnActiveSceneChanged, ActiveSceneChangedEvent));
        };

        Panel() {
            Application::GetApplicationInstance().GetEventDispatcher()->Subscribe(
                ActiveSceneChanged,
                FORWARD_CALLBACK_FUNCTION(Panel::OnActiveSceneChanged, ActiveSceneChangedEvent));
        };

        virtual void Render() = 0;

        [[nodiscard]] bool IsPanelOpen() const { return m_WindowOpen; }

        void OpenPanel() { m_WindowOpen = true; }
        void ClosePanel() { m_WindowOpen = false; }

    protected:
        bool m_WindowOpen = true;
        std::shared_ptr<Scene> m_Scene = nullptr;

        void OnActiveSceneChanged(ActiveSceneChangedEvent &e) {
            m_Scene = std::move(e.GetActiveScene());
        };
    };
} // Hamster

#endif //PANEL_H
