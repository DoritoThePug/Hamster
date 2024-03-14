#pragma once

#include <string>

#include "Events/Event.h"

namespace Hamster {
	class WindowCloseEvent : public Event {
	public:
		CLASS_BIND_EVENT_TYPE(WindowClose)
		CLASS_BIND_EVENT_CATEGORY(WindowEvent)
	};

	class WindowResizeEvent : public Event {
	public:
		CLASS_BIND_EVENT_TYPE(WindowResize)
		CLASS_BIND_EVENT_CATEGORY(WindowEvent)

		WindowResizeEvent(int width, int height): m_width(width), m_height(height) {};

		int GetHeight() { return m_height; }
		int GetWidth() { return m_width; }
	private:
		int m_width, m_height;
	};
}

