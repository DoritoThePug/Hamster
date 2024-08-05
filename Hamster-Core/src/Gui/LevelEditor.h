//
// Created by jaden on 03/08/24.
//

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <functional>
#include <utility>

#include "Renderer/FramebufferTexture.h"
#include "Events/GuiEvents.h"
#include "Core/Application.h"

namespace Hamster {
    class LevelEditor {
    public:
        LevelEditor(const std::function<void()> &renderFn, int viewportWidth, int viewportHeight);

        void Render();

        void FramebufferSizeChange(LevelEditorViewportSizeChangedEvent &e);

    private:
        std::function<void()> m_RenderFn;
        int m_ViewportWidth, m_ViewportHeight;
        FramebufferTexture m_FramebufferTexture;
        bool m_WindowOpen;
    };
} // Hamster

#endif //LEVELEDITOR_H
