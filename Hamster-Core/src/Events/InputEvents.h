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
} // Hamster

#endif //INPUTEVENTS_H
