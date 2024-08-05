#pragma once

#include <string>

#include "Event.h"
#include "Core/Base.h"

namespace Hamster {
	class WindowCloseEvent : public Event {
	public:
		BIND_EVENT_TYPE(WindowClose)
	};

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(const int width, const int height) : m_Width(width), m_Height(height) {
		}

		[[nodiscard]] int GetWidth() const { return m_Width; }
		[[nodiscard]] int GetHeight() const { return m_Height; }

		BIND_EVENT_TYPE(WindowResize)

	private:
		int m_Width, m_Height;
	};

	class FramebufferResizeEvent : public Event {
	public:
		FramebufferResizeEvent(const int width, const int height) : m_Width(width), m_Height(height) {
		}

		[[nodiscard]] int GetWidth() const { return m_Width; }
		[[nodiscard]] int GetHeight() const { return m_Height; }

		BIND_EVENT_TYPE(FramebufferResize)

	private:
		int m_Width, m_Height;
	};
}
