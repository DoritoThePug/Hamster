#pragma once

#include <string>
#include <utility>
#include <iostream>
#include <functional>

namespace Hamster {
#define BIT_F(x) 1 << x
#define CLASS_BIND_EVENT_TYPE(type) static EventType GetStaticEventType() {return EventType::type;} virtual EventType GetEventType() const override {return EventType::type;} virtual std::string GetName() const override {return #type;}
#define CLASS_BIND_EVENT_CATEGORY(category) virtual int GetEventCategoryFlags() const override {return category;}
#define FORWARD_CALLBACK_FUNCTION(func) [this](auto&&... args) -> void {return this->func(std::forward<decltype(args)>(args)...);}

	enum EventType {
		WindowClose, WindowResize
	};

	enum EventCategory {
		WindowEvent = BIT_F(0)
	};
	
	class Event {
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetEventCategoryFlags() const = 0;
		virtual std::string GetName() const = 0;
		 
		bool IsInCategory(EventCategory category) const;
	};

	class EventDispatcher {
	private:
		Event& m_Event;
	public:
		EventDispatcher(Event& e) : m_Event(e) { std::cout << e.GetName() << std::endl; };
		
		//template <typename T, typename F>
		//void Dispatch(const F& func);

		template <typename T, typename F>
		void Dispatch(const F& func) {
			if (m_Event.GetEventType() == T::GetStaticEventType()) {
				func();
			}
		}
	};
}