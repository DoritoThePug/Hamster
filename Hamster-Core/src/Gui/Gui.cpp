//
// Created by jaden on 17/07/24.
//


#include "Gui.h"

#include "Renderer/Renderer.h"
#include "Core/Window.h"
#include "LevelEditor.h"

namespace Hamster {
    Gui::Gui(GLFWwindow *window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_IO = ImGui::GetIO();
        (void) m_IO;
        m_IO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
        m_IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
        m_IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

        ImGui::StyleColorsDark();

        ImGuiStyle &style = ImGui::GetStyle();
        if (m_IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);

        ImGui_ImplOpenGL3_Init("#version 400 core");
    }

    void Gui::Start(bool *windowOpen) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        Renderer::Clear();

        ImGui::NewFrame();
    }

    void Gui::End() {
    }

    void Gui::Render() {
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (m_IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
} // Hamster
