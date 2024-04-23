#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


#include "Application.h"
#include "Window.h"
#include "Base.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Utils/AssetManager.h"

namespace Hamster {
	Application::Application() {
		std::cout << "Application created" << std::endl;
	}

	Application::~Application() {
		std::cout << "Application destroyed" << std::endl;
	}

	void foo(WindowCloseEvent& e) {
		std::cout << "hi" << std::endl;
	}

	void Application::Run() {
		std::cout << "Application running" << std::endl;

		WindowProps props;

		Window window(props);

		Renderer::Init(props.width, props.height);

		EventDispatcher dispatcher;

		window.SetWindowEventDispatcher(&dispatcher);

		dispatcher.Subscribe(WindowClose, FORWARD_CALLBACK_FUNCTION(Application::Close, WindowCloseEvent));

		glfwSetWindowCloseCallback(window.GetGLFWWindowPointer(), [](GLFWwindow* windowGLFW) {
			EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(windowGLFW);

			WindowCloseEvent e;

			dispatcher->Post<WindowCloseEvent>(e);
			});

		dispatcher.Subscribe(WindowResize, FORWARD_CALLBACK_FUNCTION(Application::ResizeWindow, WindowResizeEvent));

		glfwSetWindowSizeCallback(window.GetGLFWWindowPointer(), [](GLFWwindow* windowGLFW, int width, int height) {
			EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(windowGLFW);

			WindowResizeEvent e(width, height);

			dispatcher->Post<WindowResizeEvent>(e);
			});

		

		Texture face("C:/Users/Jaden/OneDrive/Documents/Hamster/Hamster/Hamster-Core/src/Renderer/Assets/awesomeface.png");
		AssetManager::AddTexture("face", face);

		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

		AssetManager::GetShader("sprite")->use();
		AssetManager::GetShader("sprite")->setUniformi("image", 0);
		AssetManager::GetShader("sprite")->setUniformMat4("projection", projection);

		while (m_running) {
			Renderer::SetClearColour(0.2f, 0.3f, 0.3f, 1.0f);
			Renderer::Clear();

			Renderer::DrawSprite(*AssetManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

			window.Update();
		}
	}



	void Application::Close(WindowCloseEvent& e) {
		m_running = false;

		std::cout << "Application closed" << std::endl;
	}

	void Application::ResizeWindow(WindowResizeEvent& e) {
		Renderer::SetViewport(e.GetWidth(), e.GetHeight());

		std::cout << "Window resized" << std::endl;
	}

	/*

	void Application::WindowResize(WindowResizeEvent& e) {
		std::cout << e.GetHeight() << std::endl;
	}*/
}