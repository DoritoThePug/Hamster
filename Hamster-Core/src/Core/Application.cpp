#include <iostream>



#include "Application.h"
#include "Window.h"
#include "Events/Event.h"


namespace Hamster {
	Application::Application() {
		std::cout << "Application created" << std::endl;


	}

	Application::~Application() {
		std::cout << "Application destroyed" << std::endl;
	}

	void Application::Run() {
		std::cout << "Application running" << std::endl;

		WindowProps props;

		Window window(props);

		window.SetWindowEventCallback(FORWARD_CALLBACK_FUNCTION(Application::OnEvent));

		glfwSetWindowCloseCallback(window.GetGLFWWindowPointer(), [](GLFWwindow* windowGLFW) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(windowGLFW);
			
			WindowCloseEvent e;

			data.callbackEvent(e);
			});

		glfwSetWindowSizeCallback(window.GetGLFWWindowPointer(), [](GLFWwindow* windowGLFW, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(windowGLFW);

			WindowResizeEvent e(width, height);

			data.callbackEvent(e);
			});
			
		while (m_running) {
			window.Update();
		}
	}



	void Application::Close(){
		m_running = false;

		std::cout << "Application closed" << std::endl;
	}

	void Application::WindowResize(WindowResizeEvent& e) {
		std::cout << e.GetHeight() << std::endl;
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		 
		dispatcher.Dispatch<WindowCloseEvent>(FORWARD_CALLBACK_FUNCTION(Application::Close));
		dispatcher.Dispatch<WindowResizeEvent>(FORWARD_CALLBACK_FUNCTION(Application::WindowResize));

		//dispatcher.Dispatch<WindowCloseE();
	}
}