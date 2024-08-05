//
// Created by jaden on 03/08/24.
//

#include <glad/glad.h>
#include <Renderer/Renderer.h>

#include "LevelEditor.h"

#include "imgui.h"
#include "Renderer/FramebufferTexture.h"
#include "Events/Event.h"

namespace Hamster {
  LevelEditor::LevelEditor(const std::function<void()> &renderFn, int viewportWidth, int viewportHeight) : m_RenderFn(
      renderFn), m_ViewportWidth(viewportWidth), m_ViewportHeight(viewportHeight),
    m_FramebufferTexture(viewportWidth, viewportHeight) {
  }


  void LevelEditor::Render() {
    if (!ImGui::Begin("Level Editor", &m_WindowOpen)) {
      ImGui::End();
      return;
    }

    const float levelEditorAvailWidth = ImGui::GetContentRegionAvail().x;
    const float levelEditorAvailHeight = ImGui::GetContentRegionAvail().y;

    m_FramebufferTexture.ResizeFrameBuffer(levelEditorAvailHeight, levelEditorAvailWidth);

    const ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage(
      (void *) (intptr_t) m_FramebufferTexture.GetTextureID(),
      ImVec2(pos.x, pos.y),
      ImVec2(pos.x + levelEditorAvailWidth, pos.y + levelEditorAvailHeight),
      ImVec2(0, 1),
      ImVec2(1, 0)
    );

    ImGui::End();

    glEnable(GL_SCISSOR_TEST);
    glScissor(0, 0, levelEditorAvailWidth, levelEditorAvailHeight);

    m_FramebufferTexture.Bind();
    glViewport(0, 200, 1920, 1080);
    // glClearColor(0.3f, 0.5f, 0.2f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Renderer::Clear();
    m_RenderFn();

    m_FramebufferTexture.Unbind();
    glDisable(GL_SCISSOR_TEST);
  }

  void LevelEditor::FramebufferSizeChange(LevelEditorViewportSizeChangedEvent &e) {
    m_FramebufferTexture.ResizeFrameBuffer(e.GetHeight(), e.GetWidth());
  }
} // Hamster

