//
// Created by jaden on 03/08/24.
//

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <functional>
#include <utility>

#include <GLFW/glfw3.h>

#include "Renderer/FramebufferTexture.h"
#include "Events/GuiEvents.h"
#include "Events/InputEvents.h"
#include "Core/Application.h"

namespace Hamster {
    class LevelEditor {
    public:
        LevelEditor(const std::function<void(bool)> &renderFn, int viewportWidth,
                    int viewportHeight, GLFWwindow *window);

        void Render();

        void FramebufferSizeChange(LevelEditorViewportSizeChangedEvent &e);

        void MouseClicked(MouseButtonClickedEvent &e);

    private:
        std::function<void(bool)> m_RenderFn;
        // std::function<void()> m_RenderFlatFn;
        int m_ViewportWidth, m_ViewportHeight;
        FramebufferTexture m_FramebufferTexture;
        bool m_WindowOpen = true;
        GLFWwindow *m_GLFWWindow;
    };
} // Hamster

#endif //LEVELEDITOR_H
