#include <iostream>
#include <functional>



#include "Application.h"
#include "Window.h"
#include "Base.h"


namespace Hamster {
	Application::Application() {
		std::cout << "Application created" << std::endl;
	}

	Application::~Application() {
		std::cout << "Application destroyed" << std::endl;
	}

	void foo(WindowCloseEvent& e) {
		std::cout << "hi" << std::endl;
	}

	void Application::Run() {
		std::cout << "Application running" << std::endl;

		WindowProps props;

		Window window(props);

		EventDispatcher dispatcher;

		window.SetWindowEventDispatcher(&dispatcher);

		dispatcher.Subscribe(WindowClose, FORWARD_CALLBACK_FUNCTION(Application::Close, WindowCloseEvent));

		glfwSetWindowCloseCallback(window.GetGLFWWindowPointer(), [](GLFWwindow* windowGLFW) {
			EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(windowGLFW);

			WindowCloseEvent e;

			dispatcher->Post<WindowCloseEvent>(e);
			});



		while (m_running) {
			window.Update();
		}
	}



	void Application::Close(WindowCloseEvent& e) {
		m_running = false;

		std::cout << "Application closed" << std::endl;
	}

	/*

	void Application::WindowResize(WindowResizeEvent& e) {
		std::cout << e.GetHeight() << std::endl;
	}*/
}