#pragma once


#include <memory>


#include "Events/Event.h"
#include "Events/WindowEvents.h"
#include "Window.h"
#include "LayerStack.h"

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <glm/glm.hpp>


#include "Scene.h"
#include "Gui/ImGuiLayer.h"
#include "Renderer/Texture.h"
#include "UUID.h"

namespace Hamster {


	class GameObject;

	//class EventDispatcher;

	class Application {

	public:
		Application();

		~Application();

		void Run();

		void Close(WindowCloseEvent &e);

		glm::mat4 GetProjectionMatrix();

		static Application& GetApplicationInstance() {return *s_Instance;}

		static void ResizeWindow(WindowResizeEvent &e);

		static void ResizeFramebuffer(FramebufferResizeEvent &e);

		void PauseSimulation();
		void ResumeSimulation();
		bool IsSimulationPaused();

		GLFWwindow* GetWindow() { return m_Window->GetGLFWWindowPointer(); }

		//void AddGameObject(GameObjectCreatedEvent& e);
		void AddGameObject(GameObject &gameObject);

		void RemoveGameObject(int ID);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);


		[[nodiscard]] int GetViewportHeight() const { return m_ViewportHeight; }
		[[nodiscard]] int GetViewportWidth() const { return m_ViewportWidth; }

		void SetViewportHeight(const int height) { m_ViewportHeight = height; }
		void SetViewportWidth(const int width) { m_ViewportWidth = width; }

		static glm::vec3 IdToColour(int id);
		static int ColourToId(glm::vec3 colour);

		// ECS

		[[nodiscard]] entt::registry &GetRegistry() { return m_Registry; }

		void UpdateSystem(entt::registry &registry);

		void RenderSystem(entt::registry &registry, bool renderFlat);

		void AddScene(std::shared_ptr<Scene> scene);
		void RemoveScene(UUID uuid);
		void SetSceneActive(UUID uuid);

	private:
		static Application *s_Instance;

		bool m_Running = true;
		bool m_IsSimulationPaused = true;

		int m_ViewportWidth = 1920;
		int m_ViewportHeight = 1080;

		glm::mat4 m_Projection;

		std::unique_ptr<EventDispatcher> m_Dispatcher;
		LayerStack m_LayerStack;

		ImGuiLayer m_ImGuiLayer;


		// ID, GameObject
		std::map<int, GameObject *> m_GameObjects;
		//Window m_Window;
		std::unique_ptr<Window> m_Window;

		std::unordered_map<UUID, std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene = nullptr;

		WindowProps m_WindowProps;

		// ECS
		entt::registry m_Registry;
	};
}
