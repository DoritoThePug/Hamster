//
// Created by jaden on 03/08/24.
//

#include <glad/glad.h>
#include <Renderer/Renderer.h>

#include <utility>

#include "LevelEditor.h"

#include "imgui.h"
#include "Renderer/FramebufferTexture.h"
#include "Events/Event.h"
#include "Core/Base.h"

namespace Hamster {
  LevelEditor::LevelEditor(const std::function<void(bool)> &renderFn,
                           int viewportWidth, int viewportHeight,
                           GLFWwindow *window) : m_RenderFn(
                                                   renderFn),
                                                 m_ViewportWidth(viewportWidth),
                                                 m_ViewportHeight(viewportHeight),
                                                 m_FramebufferTexture(viewportWidth, viewportHeight),
                                                 m_GLFWWindow(window) {
    // auto *dispatcher = static_cast<EventDispatcher *>(glfwGetWindowUserPointer(m_GLFWWindow));
    //
    // dispatcher->Subscribe(
    //   MouseButtonClicked,
    //   FORWARD_CALLBACK_FUNCTION(LevelEditor::MouseClicked, MouseButtonClickedEvent));
  }


  void LevelEditor::Render() {
    // 1080
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(1936, 1115));

    int x, y;

    glfwGetFramebufferSize(m_GLFWWindow, &x, &y);

    // std::cout << x << " " << y << std::endl;

    if (!ImGui::Begin("Level Editor", &m_WindowOpen)) {
      ImGui::End();
      return;
    }

    const float levelEditorAvailWidth = ImGui::GetContentRegionAvail().x;
    const float levelEditorAvailHeight = ImGui::GetContentRegionAvail().y;




    ImGuiIO io = ImGui::GetIO();
    (void) io;

    if (io.WantCaptureMouse && ImGui::IsMouseClicked(0)) {
      const ImVec2 mousePos = ImGui::GetMousePos();
      const ImVec2 windowPos = ImGui::GetWindowPos();
      const ImVec2 windowSize = ImGui::GetWindowSize();
      const ImVec2 windowBorderSize = ImGui::GetStyle().WindowPadding;

      float viewportPosX = mousePos.x - windowPos.x - (windowSize.x-levelEditorAvailWidth)/2;
      float viewportPosY = mousePos.y - windowPos.y - (windowSize.y-levelEditorAvailHeight-windowBorderSize.y) + (1080-levelEditorAvailHeight);

      // std::cout << windowSize.y - ImGui::GetContentRegionAvail().y - windowBorderSize.y << std::endl;
      // std::cout << viewportPosX << " " << viewportPosY << std::endl;

      glEnable(GL_SCISSOR_TEST);
      glScissor(0, 0, levelEditorAvailWidth, levelEditorAvailHeight);
      m_FramebufferTexture.Bind();
      glViewport(0, 0, 1920, 1080);
      Renderer::Clear();
      m_RenderFn(true);
      // glFlush();
      // glFinish();
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      int width, height;
      glfwGetFramebufferSize(m_GLFWWindow, &width, &height);

      // std::cout << width << " " << height << std::endl;

      unsigned char data[4];


      glReadPixels(viewportPosX, 1080-viewportPosY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

      m_FramebufferTexture.Unbind();
      glDisable(GL_SCISSOR_TEST);

      Renderer::Clear();

      int pickedID =
          data[0] +
          data[1] * 256 +
          data[2] * 256 * 256;

      std::cout << viewportPosX << " " << viewportPosY << " " << pickedID - 1 << std::endl;

      // int x,y;


      // std::cout << glfwGetFramebufferSize(m_GLF)

      // data = {1,2,3,4};

      std::cout << (float) data[0] << " " << (float) data[1] << " " << (float) data[2] << std::endl;
    }

    // ImGui::SetConten

    m_FramebufferTexture.ResizeFrameBuffer(levelEditorAvailHeight, levelEditorAvailWidth);

    const ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage(
      (void *) (intptr_t) m_FramebufferTexture.GetTextureID(),
      ImVec2(pos.x, pos.y),
      ImVec2(pos.x + levelEditorAvailWidth, pos.y + levelEditorAvailHeight),
      ImVec2(0, 1),
      ImVec2(1, 0)
    );



    glEnable(GL_SCISSOR_TEST);
    glScissor(0, 0, levelEditorAvailWidth, levelEditorAvailHeight);

    // std::cout << levelEditorAvailHeight << " " << levelEditorAvailWidth << " hi" << std::endl;

    m_FramebufferTexture.Bind();
    glViewport(0, 0, 1920, 1080);
    // glClearColor(0.3f, 0.5f, 0.2f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Renderer::Clear();
    m_RenderFn(false);

    // unsigned char data[4];
    // glReadPixels(150, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //
    // int pickedID =
    //     data[0] +
    //     data[1] * 256 +
    //     data[2] * 256 * 256;

    // std::cout << (int) data[0] << " " << (int) data[1] << " " << (int) data[2] << std::endl;

    m_FramebufferTexture.Unbind();
    glDisable(GL_SCISSOR_TEST);


    ImGui::End();
  }

  void LevelEditor::FramebufferSizeChange(LevelEditorViewportSizeChangedEvent &e) {
    m_FramebufferTexture.ResizeFrameBuffer(e.GetHeight(), e.GetWidth());
  }

  // void LevelEditor::MouseClicked(MouseButtonClickedEvent &e) {
  //   std::cout << m_WindowOpen << std::endl;
  //
  //   if (m_WindowOpen) {
  //     // ImVec2 windowPos = ImGui::GetWindowPos();
  //
  //     // std::cout << e.GetXPos() - windowPos.x << " " << e.GetYPos() - windowPos.y << std::endl;
  //   }
  // }
} // Hamster