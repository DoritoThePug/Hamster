//
// Created by Jaden on 23/08/2024.
//

#ifndef EDITOR_H
#define EDITOR_H

#include <glm/glm.hpp>
#include <imgui.h>
#include <functional>
#include <memory>

#include <Core/Layer.h>
#include <Renderer/FramebufferTexture.h>

#include "GLFW/glfw3.h"
#include "Panels/PropertyEditor.h"

class EditorLayer : public Hamster::Layer {
    public:
    explicit EditorLayer(const std::function<void(bool)> &renderFn, GLFWwindow *window);

    void OnAttach() override;

    void OnUpdate() override;
    void OnImGuiUpdate() override;
private:
    bool m_WindowOpen = true;

    std::function<void(bool)> m_RenderFn;

    ImVec2 m_LevelEditorAvailRegion = {0.0f, 0.0f};
    glm::vec2 m_ViewportOffset = {0.0f, 0.0f};
    Hamster::FramebufferTexture m_FramebufferTexture;

    std::unique_ptr<PropertyEditor> m_PropertyEditor = std::make_unique<PropertyEditor>();

    GLFWwindow *m_Window;

    int m_ViewportWidth = 1920;
    int m_ViewportHeight = 1080;
};



#endif //EDITOR_H
