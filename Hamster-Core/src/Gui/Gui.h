//
// Created by jaden on 17/07/24.
//

#ifndef GUI_H
#define GUI_H

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "LevelEditor.h"

namespace Hamster {
    class Gui {
    public:
        Gui(GLFWwindow *window);

        void Start(bool *windowOpen);

        void End();

        void Render();

    private:
        ImGuiIO m_IO;
        // LevelEditor m_LevelEditorWindow;
    };
} // Hamster

#endif //GUI_H