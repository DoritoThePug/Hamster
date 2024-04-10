#include "Event.h"

namespace Hamster {
	void EventDispatcher::Subscribe(EventType e, std::function<void(const Event&)>&& fn) {
		m_Observers[e].push_back(fn);
	}
}