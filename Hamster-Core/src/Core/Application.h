#pragma once


#include <memory>


#include "Events/Event.h"
#include "Events/WindowEvents.h"
#include "Window.h"

#include <GLFW/glfw3.h>

namespace Hamster {
	class GameObject;

	//class EventDispatcher;

	class Application
	{
	private:
		bool m_running = true;

		std::unique_ptr<EventDispatcher> m_Dispatcher;

		// ID, GameObject
		std::map<int, GameObject*> m_GameObjects;
		//Window m_Window;
		std::unique_ptr<Window> m_Window;

		//WindowProps m_WindowProps;
	public:
		Application();
		~Application();

		void Run();
		void Close(WindowCloseEvent& e);
		void ResizeWindow(WindowResizeEvent& e);

		//void AddGameObject(GameObjectCreatedEvent& e);
		void AddGameObject(GameObject& gameObject);
		void RemoveGameObject(int ID);

		void RenderScene();
		void UpdateScene(float deltaTime);
	};
}