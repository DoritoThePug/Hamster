#pragma once

#include <map>
#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace Hamster {
#define BIND_EVENT_TYPE(type) static EventType GetStaticEventType() {return EventType::type;} virtual EventType GetEventType() const override {return GetStaticEventType();} virtual std::string GetEventName() const override {return #type;}
#define FORWARD_CALLBACK_FUNCTION(func) [this](auto&&... args) -> void {return this->func(std::forward<decltype(args)>(args)...);}


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
		void Subscribe(EventType e, std::function<void(const Event&)>&& fn);

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
		std::map < EventType, std::vector<std::function<void(const Event&)>>> m_Observers;
	};
}
