#pragma once

#include <string>
#include <stdint.h>

#include "Event.h"
#include "Core/Base.h"

namespace Hamster {
	class WindowCloseEvent : public Event {
	public:
		BIND_EVENT_TYPE(WindowClose)
	};

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint16_t width, uint16_t height) : m_Width(width), m_Height(height) {}

		uint16_t GetWidth() { return m_Width; }
		uint16_t GetHeight() { return m_Height; }

		BIND_EVENT_TYPE(WindowResize)
	private:
		uint16_t m_Width, m_Height;
	};
}