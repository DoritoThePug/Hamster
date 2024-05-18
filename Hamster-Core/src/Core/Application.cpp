#include <iostream>

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Application.h"

#include "Base.h"

#include "GameObject.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Utils/AssetManager.h"

namespace Hamster {
Application::Application() {
  std::cout << "Application created" << std::endl;

  WindowProps props;

  // Window* window = new Window(props);

  // m_Window = std::unique_ptr<Window> (new Window(props));
  m_Window = std::make_unique<Window>(props);

  Renderer::Init(props.width, props.height);

  // EventDispatcher* dispatcher = new EventDispatcher;
  m_Dispatcher = std::unique_ptr<EventDispatcher>(new EventDispatcher);

  m_Window->SetWindowEventDispatcher(m_Dispatcher.get());

  m_Dispatcher->Subscribe(
      WindowClose,
      FORWARD_CALLBACK_FUNCTION(Application::Close, WindowCloseEvent));

  glfwSetWindowCloseCallback(
      m_Window->GetGLFWWindowPointer(), [](GLFWwindow *windowGLFW) {
        EventDispatcher *dispatcher =
            (EventDispatcher *)glfwGetWindowUserPointer(windowGLFW);

        WindowCloseEvent e;

        dispatcher->Post<WindowCloseEvent>(e);
      });

  m_Dispatcher->Subscribe(
      WindowResize,
      FORWARD_CALLBACK_FUNCTION(Application::ResizeWindow, WindowResizeEvent));

  glfwSetWindowSizeCallback(m_Window->GetGLFWWindowPointer(),
                            [](GLFWwindow *windowGLFW, int width, int height) {
                              EventDispatcher *dispatcher =
                                  (EventDispatcher *)glfwGetWindowUserPointer(
                                      windowGLFW);

                              WindowResizeEvent e(width, height);

                              dispatcher->Post<WindowResizeEvent>(e);
                            });
}

Application::~Application() {
  std::cout << "Application destroyed" << std::endl;
}

void Application::Run() {
  std::cout << "Application running" << std::endl;

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

  AssetManager::GetShader("sprite")->use();
  AssetManager::GetShader("sprite")->setUniformi("image", 0);
  AssetManager::GetShader("sprite")->setUniformMat4("projection", projection);

  while (m_running) {
    Renderer::SetClearColour(0.2f, 0.3f, 0.3f, 1.0f);
    Renderer::Clear();

    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    UpdateScene(deltaTime);

    RenderScene();

    m_Window->Update();
  }
}

void Application::Close(WindowCloseEvent &e) {
  m_running = false;
  m_Window.reset();

  AssetManager::Terminate();

  std::cout << "Application closed" << std::endl;
}

void Application::ResizeWindow(WindowResizeEvent &e) {
  Renderer::SetViewport(e.GetWidth(), e.GetHeight());

  std::cout << "Window resized" << std::endl;
}

void Application::AddGameObject(GameObject &gameObject) {
  m_GameObjects[gameObject.GetID()] = &gameObject;
}

void Application::RemoveGameObject(int ID) { m_GameObjects.erase(ID); }

void Application::RenderScene() {
  for (const auto &pair : m_GameObjects) {
    pair.second->Draw();
  }
}

void Application::UpdateScene(float deltaTime) {
  for (const auto &pair : m_GameObjects) {
    pair.second->OnUpdate(deltaTime);
  }
}
} // namespace Hamster
