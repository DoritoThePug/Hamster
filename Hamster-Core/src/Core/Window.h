#pragma once

#include <string>
#include <functional>

#include <GLFW/glfw3.h>

#include "Events/Event.h"


namespace Hamster {
	struct WindowData {
		uint16_t height, width;
		std::string title;
	};

	struct WindowProps {
		uint16_t height, width;
		std::string title;

		WindowProps(uint16_t height = 600, uint16_t width = 800, std::string title = "Hamster") : height(height), width(width), title(title) {};
	};

	class Window
	{
	private:
		GLFWwindow* m_Window;
		WindowData m_WindowData;
	public:
		Window(const WindowProps& props);
		~Window();

		GLFWwindow* GetGLFWWindowPointer();

		void SetWindowEventDispatcher(EventDispatcher* dispatcher);

		void Update();

		static void TerminateAllWindows();
	};
}
