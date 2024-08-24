//
// Created by Jaden on 23/08/2024.
//

#include "EditorLayer.h"

#include <iostream>
#include <glad/glad.h>

#include <Renderer/Renderer.h>

EditorLayer::EditorLayer(const std::function<void(bool)> &renderFn, GLFWwindow* window) : m_RenderFn(renderFn), m_FramebufferTexture(1920, 1080), m_Window(window) {
}

void EditorLayer::OnAttach() {

}

void EditorLayer::OnUpdate() {
    // std::cout << "hi" << std::endl;

    if (ImGui::IsMouseClicked(0))
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(0, 0, m_LevelEditorAvailRegion.x, m_LevelEditorAvailRegion.y);

        m_FramebufferTexture.Bind();
        glViewport(0, 0, m_ViewportWidth, m_ViewportHeight);
        Hamster::Renderer::Clear();
        m_RenderFn(true);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        unsigned char data[4];

        const ImVec2 imGuiMousePos = ImGui::GetMousePos();

        float mousePosX = imGuiMousePos.x - m_ViewportOffset.x;
        float mousePosY = imGuiMousePos.y - m_ViewportOffset.y;





        // dont forget to check mousepos is valid
        glReadPixels(mousePosX, m_ViewportHeight-mousePosY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

        m_FramebufferTexture.Unbind();
        glDisable(GL_SCISSOR_TEST);

        Hamster::Renderer::Clear();

        int pickedID =
            data[0] +
            data[1] * 256 +
            data[2] * 256 * 256;

        std::cout << pickedID - 1<< std::endl;
    }

    m_FramebufferTexture.ResizeFrameBuffer(m_LevelEditorAvailRegion.x, m_LevelEditorAvailRegion.y);

    glEnable(GL_SCISSOR_TEST);
    glScissor(0, 0, m_LevelEditorAvailRegion.x, m_LevelEditorAvailRegion.y);


    m_FramebufferTexture.Bind();
    glViewport(0, 0, m_ViewportWidth, m_ViewportHeight);


    Hamster::Renderer::Clear();
    m_RenderFn(false);

    m_FramebufferTexture.Unbind();
    glDisable(GL_SCISSOR_TEST);
}

void EditorLayer::OnImGuiUpdate() {
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(1936, 1115));
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    if (!ImGui::Begin("Level Editor", &m_WindowOpen)) {
        ImGui::End();
        return;
    }


    m_LevelEditorAvailRegion = ImGui::GetContentRegionAvail();
    const ImVec2 windowPos = ImGui::GetWindowPos();
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const ImVec2 windowBorderSize = ImGui::GetStyle().WindowPadding;

    m_ViewportOffset.x = windowPos.x + (windowSize.x-m_LevelEditorAvailRegion.x)/2;
    m_ViewportOffset.y = windowPos.y + (windowSize.y-m_LevelEditorAvailRegion.y-windowBorderSize.y) - (1080-m_LevelEditorAvailRegion.y);


    const ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage(
      (void *) (intptr_t) m_FramebufferTexture.GetTextureID(),
      ImVec2(pos.x, pos.y),
      ImVec2(pos.x + m_LevelEditorAvailRegion.x, pos.y + m_LevelEditorAvailRegion.y),
      ImVec2(0, 1),
      ImVec2(1, 0)
    );

    ImGui::End();

    if (m_PropertyEditor->IsPanelOpen()) {
        m_PropertyEditor->Render();
    }
}

