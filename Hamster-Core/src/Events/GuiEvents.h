//
// Created by jaden on 04/08/24.
//

#ifndef GUIEVENTS_H
#define GUIEVENTS_H

#include "Event.h"
#include "Core/Base.h"

namespace Hamster {
    class LevelEditorViewportSizeChangedEvent : public Event {
    public:
        LevelEditorViewportSizeChangedEvent(const int width, const int height) : m_Width(width), m_Height(height) {
        }

        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }

        BIND_EVENT_TYPE(LevelEditorViewportSizeChanged);

    private:
        int m_Width, m_Height;
    };;
} // Hamster

#endif //GUIEVENTS_H
