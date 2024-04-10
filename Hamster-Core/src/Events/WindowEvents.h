#pragma once

#include <string>

#include "Event.h"
#include "Core/Base.h"

namespace Hamster {
	class WindowCloseEvent : public Event {
	public:
		BIND_EVENT_TYPE(WindowClose)
	};
}