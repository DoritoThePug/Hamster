//
// Created by jaden on 02/08/24.
//

#include "HamsterPCH.h"

#include "Core/Base.h"
#include "Events/Event.h"
#include "Events/InputEvents.h"
#include "InputManager.h"

namespace Hamster {
InputManager::InputManager(GLFWwindow *window) : m_Window(window) {
  m_EventDispatcher =
      static_cast<EventDispatcher *>(glfwGetWindowUserPointer(window));

  // m_EventDispatcher->Subscribe(
  //     KeyPressed,
  //     FORWARD_CALLBACK_FUNCTION(InputManager::KeyPressed, KeyPressedEvent));

  // glfwSetKeyCallback(m_Window, );

  glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *windowGLFW, int button,
                                          int action, int mods) {
    auto *dispatcher =
        static_cast<EventDispatcher *>(glfwGetWindowUserPointer(windowGLFW));

    double xpos, ypos;
    glfwGetCursorPos(windowGLFW, &xpos, &ypos);

    // std::cout << xpos << " " << ypos << std::endl;

    if (action == Pressed) {
      MouseButtonClickedEvent e(static_cast<MouseButtons>(button), xpos, ypos);

      // std::cout << "hi" << std::endl;

      dispatcher->Post<MouseButtonClickedEvent>(e);
    }

    // std::cout << "hi2" << std::endl;
  });
}
} // namespace Hamster
