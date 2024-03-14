#pragma once

#include "Events/Event.h"
#include "Events/WindowEvents.h"

#include <glfw3.h>

namespace Hamster {
	class Application
	{
	private:
		bool m_running = true;
		//GLFWwindow* m_appWindow;

	public:
		Application();
		~Application();

		void Run();
		void Close();
		
		void WindowResize(WindowResizeEvent& e);

		void OnEvent(Event& e);
	};
}

