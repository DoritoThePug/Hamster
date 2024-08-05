#include <iostream>

#include <glad/glad.h>

#include "Application.h"
#include "Window.h"

static uint8_t s_NumWindows = 0;

namespace Hamster {
Window::Window(const WindowProps &props) {
  if (glfwInit()) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  } else {
    std::cout << "glfw failed to initialise" << std::endl;
  }

  /*glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

  GLFWwindow *window = glfwCreateWindow(props.width, props.height,
                                        props.title.c_str(), NULL, NULL);

  if (window == NULL) {
    std::cout << "Window creation failed" << std::endl;
  } else {
    s_NumWindows += 1;
  }

  m_Window = window;

  glfwMakeContextCurrent(window);
  // glViewport(0, 0, 800, 600);

  m_WindowData.height = props.height;
  m_WindowData.width = props.width;
  m_WindowData.title = props.title;
}

Window::~Window() {
  // s_NumWindows -= 1;
  glfwDestroyWindow(m_Window);

  glfwTerminate();

  // if (s_NumWindows == 0) {
  //   std::cout << "here" << std::endl;

  //   glfwTerminate();
  // } else {
  //   glfwDestroyWindow(m_Window);
  // }
}

GLFWwindow *Window::GetGLFWWindowPointer() { return m_Window; }

void Window::SetWindowEventDispatcher(EventDispatcher *dispatcher) {
  glfwSetWindowUserPointer(m_Window, dispatcher);
}

void Window::Update(bool running) {
  glfwPollEvents();








  // if (show_another_window)
  // {
  //   ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  //   ImGui::Text("Hello from another window!");
  //   if (ImGui::Button("Close Me"))
  //     show_another_window = false;
  //   ImGui::End();
  // }

  // ImGui::ShowDemoWindow();
  //
  // ImGui::End();
  // ImGui::Render();
  //
  //
  //
  // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  // if (m_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  // {
  //   GLFWwindow* backup_current_context = glfwGetCurrentContext();
  //   ImGui::UpdatePlatformWindows();
  //   ImGui::RenderPlatformWindowsDefault();
  //   glfwMakeContextCurrent(backup_current_context);
  // }

  glfwSwapBuffers(m_Window);
  
}

void Window::TerminateAllWindows() { glfwTerminate(); }
} // namespace Hamster
