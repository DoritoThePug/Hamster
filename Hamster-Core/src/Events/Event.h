#pragma once

#include <map>
#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace Hamster {



	enum EventType {
		WindowClose, WindowResize
	};

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual std::string GetEventName() const = 0;
	};

	class EventDispatcher {
	public:
		void Subscribe(EventType e, std::function<void(Event&)> fn);

		template <typename T>
		void Post(Event& e) {

			std::cout << e.GetEventName() << std::endl;

			if (m_Observers.find(e.GetEventType()) == m_Observers.end()) {
				return;
			}

			auto&& observers = m_Observers.at(static_cast<T&>(e).GetEventType());


			for (auto&& observer : observers) {
				observer(static_cast<T&>(e));
			}
		}
	private:
		std::map < EventType, std::vector<std::function<void(Event&)>>> m_Observers;
	};
}
