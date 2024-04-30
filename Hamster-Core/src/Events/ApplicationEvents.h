//#pragma once
//
//#include "Core/Base.h"
//#include "Core/GameObject.h"
//#include "Event.h"
//
//namespace Hamster {
//	class GameObjectCreatedEvent : public Event {
//	public:
//		GameObjectCreatedEvent(GameObject& gameObject) : m_GameObject(gameObject) { ; }
//
//		GameObject& GetGameObject() { return m_GameObject; }
//
//		BIND_EVENT_TYPE(GameObjectCreate)
//	private: 
//		GameObject& m_GameObject;
//	};
//}