#include <iostream>

#include "Window.h"
#include "Application.h"

static uint8_t s_NumWindows = 0;

namespace Hamster {
	Window::Window(WindowProps& props) {
		if (s_NumWindows == 0) {
			glfwInit();
		}

		GLFWwindow* window = glfwCreateWindow(props.width, props.height, props.title.c_str(), NULL, NULL);

		if (window == NULL) {
			std::cout << "Window creation failed" << std::endl;
		}
		else {
			s_NumWindows += 1;
		}

		m_Window = window;

		glfwMakeContextCurrent(window);

		m_WindowData.height = props.height;
		m_WindowData.width = props.width;
		m_WindowData.title = props.title;

		glfwSetWindowUserPointer(m_Window, &m_WindowData);


	}

	Window::~Window() {
		s_NumWindows -= 1;

		if (s_NumWindows == 0) {
			glfwTerminate();
		}
		else {
			glfwDestroyWindow(m_Window);
		}
	}

	GLFWwindow* Window::GetGLFWWindowPointer() {
		return m_Window;
	}


	void Window::SetWindowEventDispatcher(EventDispatcher* dispatcher) {
		glfwSetWindowUserPointer(m_Window, dispatcher);
	}

	void Window::Update() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::TerminateAllWindows() {
		glfwTerminate();
	}
}