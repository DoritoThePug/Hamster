#pragma once


#include <memory>


#include "Events/Event.h"
#include "Events/WindowEvents.h"
#include "Window.h"
#include "LayerStack.h"

#include <GLFW/glfw3.h>

namespace Hamster {
	class GameObject;

	//class EventDispatcher;

	class Application {
	public:
		Application();

		~Application();

		void Run();

		void Close(WindowCloseEvent &e);

		static void ResizeWindow(WindowResizeEvent &e);

		static void ResizeFramebuffer(FramebufferResizeEvent &e);

		//void AddGameObject(GameObjectCreatedEvent& e);
		void AddGameObject(GameObject &gameObject);

		void RemoveGameObject(int ID);

		void RenderScene() const;

		void UpdateScene(float deltaTime) const;

		[[nodiscard]] int GetViewportHeight() const { return m_ViewportHeight; }
		[[nodiscard]] int GetViewportWidth() const { return m_ViewportWidth; }

		void SetViewportHeight(const int height) { m_ViewportHeight = height; }
		void SetViewportWidth(const int width) { m_ViewportWidth = width; }

	private:
		bool m_running = true;

		int m_ViewportWidth = 1920;
		int m_ViewportHeight = 1080;

		std::unique_ptr<EventDispatcher> m_Dispatcher;

		// ID, GameObject
		std::map<int, GameObject *> m_GameObjects;
		//Window m_Window;
		std::unique_ptr<Window> m_Window;

		WindowProps m_WindowProps;
	};
}
