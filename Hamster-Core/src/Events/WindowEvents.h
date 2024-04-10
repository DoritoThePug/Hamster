#pragma once

#include <string>

#include "Events/Event.h"

namespace Hamster {
	class WindowCloseEvent : public Event {
	public:
		BIND_EVENT_TYPE(WindowClose)
	};
}