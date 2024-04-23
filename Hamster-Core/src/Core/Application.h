#pragma once

#include "Events/Event.h"
#include "Events/WindowEvents.h"

#include <glfw3.h>

namespace Hamster {
	class Application
	{
	private:
		bool m_running = true;

		EventDispatcher m_Dispatcher;
	public:

		Application();
		~Application();

		void Run();
		void Close(WindowCloseEvent& e);
		void ResizeWindow(WindowResizeEvent& e);
	};
}