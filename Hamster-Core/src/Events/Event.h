#pragma once

#include <map>
#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace Hamster {
	enum EventType {
		// Window Events
		WindowClose, WindowResize, FramebufferResize,

		// GUI Events
		LevelEditorViewportSizeChanged,

		// Input Events
		KeyPressed, KeyReleased, MouseButtonClicked,

		// Application Events
		ActiveSceneChanged, ProjectOpened, SceneCreated
	};

	class Event {
	public:
		[[nodiscard]] virtual EventType GetEventType() const = 0;

		[[nodiscard]] virtual std::string GetEventName() const = 0;

		[[nodiscard]] bool IsHandled() const { return m_Handled; }
		void Handled() { m_Handled = true; }

	private:
		bool m_Handled = false;
	};

	class EventDispatcher {
	public:
		void Subscribe(EventType e, std::function<void(Event &)> fn);

		template<typename T>
		void Post(Event &e) {
			if (m_Observers.find(e.GetEventType()) == m_Observers.end()) {
				return;
			}

			auto &&observers = m_Observers.at(static_cast<T &>(e).GetEventType());

			for (auto &&observer: observers) {
				observer(static_cast<T &>(e));
			}
		}

	private:
		std::map<EventType, std::vector<std::function<void(Event &)> > > m_Observers;
	};
}
