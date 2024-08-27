//
// Created by Jaden on 23/08/2024.
//

#ifndef EDITOR_H
#define EDITOR_H

#include <glm/glm.hpp>
#include <imgui.h>
#include <functional>
#include <memory>



#include "GLFW/glfw3.h"

#include <Hamster.h>
#include <Renderer/FramebufferTexture.h>

#include "Panels/StartPauseModal.h"
#include "Panels/Hierarchy.h"
#include "Panels/PropertyEditor.h"

class EditorLayer : public Hamster::Layer {
    public:
    explicit EditorLayer(const std::function<void(bool)> &renderFn,  Hamster::Application& app);

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
    std::unique_ptr<Hierarchy> m_Hierarchy;

    std::unique_ptr<StartPauseModal> m_StartPauseModal;

    Hamster::Application& m_App;

    int m_ViewportWidth = 1920;
    int m_ViewportHeight = 1080;

    bool xGuizmoHeld = false;
    bool yGuizmoHeld = false;
    float mouseHeldOffsetX = 0.0f;
    float mouseHeldOffsetY = 0.0f;
};



#endif //EDITOR_H
