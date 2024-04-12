#pragma once

//#include "Events/EventOld.h"
#include "Events/Event.h"
#include "Events/WindowEvents.h"
/*
#include "Events/WindowEventsOld.h"*/

#include <glfw3.h>

namespace Hamster {
	class Application
	{
	private:
		bool m_running = true;
		//GLFWwindow* m_appWindow;

		EventDispatcher m_Dispatcher;
	public:

		Application();
		~Application();

		void Run();
		void Close(WindowCloseEvent& e);
		void ResizeWindow(WindowResizeEvent& e);

		/*
		void WindowResize(WindowResizeEvent& e);

		void OnEvent(Event& e);*/
	};
}

