#pragma once

#include <functional>
#include <string>

#include <GLFW/glfw3.h>
// #include <imgui.h>
// #include <imgui_impl_glfw.h>
// #include <imgui_impl_opengl3.h>

#include "Events/Event.h"

namespace Hamster {
  struct WindowData {
    float height, width;
    std::string title;
  };

  struct WindowProps {
    float height, width;
    std::string title;

    WindowProps(float height = 500, float width = 500,
                std::string title = "Hamster")
      : height(height), width(width), title(title) {
    };
  };

  class Window {
  public:
    Window(const WindowProps &props);

    ~Window();

    GLFWwindow *GetGLFWWindowPointer();

    void SetWindowEventDispatcher(EventDispatcher *dispatcher);

    void Update(bool running);

    static void TerminateAllWindows();

  private:
    GLFWwindow *m_Window;
    WindowData m_WindowData;
    bool show_another_window = true;
  };
} // namespace Hamster
