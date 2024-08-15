#pragma once

#include <functional>
#include <string>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Events/Event.h"

namespace Hamster {
struct WindowData {
  uint16_t height, width;
  std::string title;
};

struct WindowProps {
  uint16_t height, width;
  std::string title;

  WindowProps(uint16_t height = 600, uint16_t width = 800,
              std::string title = "Hamster")
      : height(height), width(width), title(title){};
};

class Window {
private:
  GLFWwindow *m_Window;
  WindowData m_WindowData;
  bool show_another_window = true;
  ImGuiIO m_io;

public:
  Window(const WindowProps &props);
  ~Window();

  GLFWwindow *GetGLFWWindowPointer();

  void SetWindowEventDispatcher(EventDispatcher *dispatcher);

  void Update(bool running);

  static void TerminateAllWindows();
};
} // namespace Hamster
