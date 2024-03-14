#include "Event.h"
#include "Events/WindowEvents.h"

namespace Hamster {
	bool Event::IsInCategory(EventCategory category) const {
		return category & GetEventCategoryFlags();
	}

	

	
}