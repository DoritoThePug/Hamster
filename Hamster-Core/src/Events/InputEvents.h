//
// Created by jaden on 02/08/24.
//

#ifndef INPUTEVENTS_H
#define INPUTEVENTS_H

#include "Event.h"
#include "Utils/InputManager.h"
#include "Core/Base.h"

namespace Hamster {
    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(KeyCodes keyCode) : m_KeyCodePressed(keyCode) {
        };

        BIND_EVENT_TYPE(KeyPressed)

    private:
        KeyCodes m_KeyCodePressed;
    };

    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(KeyCodes keyCode) : m_KeyCodeReleased(keyCode) {
        };

        BIND_EVENT_TYPE(KeyReleased)

    private:
        KeyCodes m_KeyCodeReleased;
    };

    class MouseButtonClickedEvent : public Event {
    public:
        MouseButtonClickedEvent(MouseButtons mouseButton, double xPos, double yPos) : m_MouseButton(mouseButton),
            m_XPos(xPos), m_YPos(yPos) {
        };

        [[nodiscard]] MouseButtons GetMouseButton() { return m_MouseButton; }

        [[nodiscard]] double GetXPos() { return m_XPos; }

        [[nodiscard]] double GetYPos() { return m_YPos; }

        BIND_EVENT_TYPE(MouseButtonClicked)

    private:
        MouseButtons m_MouseButton;
        double m_XPos, m_YPos;
    };
} // Hamster

#endif //INPUTEVENTS_H
