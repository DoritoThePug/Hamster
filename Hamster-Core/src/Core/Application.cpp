#include <iostream>

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <imgui.h>
#include <functional>

#include "Application.h"

#include "Base.h"

#include "GameObject.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/FramebufferTexture.h"
#include "Utils/AssetManager.h"
#include "Gui/Gui.h"
#include "Gui/LevelEditor.h"

namespace Hamster {
  Application::Application() {
    std::cout << "Application created" << std::endl;

    m_Window = std::make_unique<Window>(m_WindowProps);

    Renderer::Init(m_ViewportHeight, m_ViewportWidth);

    // glViewport(0, 0, 800, 600);

    m_Dispatcher = std::make_unique<EventDispatcher>();

    m_Window->SetWindowEventDispatcher(m_Dispatcher.get());

    m_Dispatcher->Subscribe(
      WindowClose,
      FORWARD_CALLBACK_FUNCTION(Application::Close, WindowCloseEvent));

    glfwSetWindowCloseCallback(
      m_Window->GetGLFWWindowPointer(), [](GLFWwindow *windowGLFW) {
        auto *dispatcher =
            static_cast<EventDispatcher *>(glfwGetWindowUserPointer(windowGLFW));

        WindowCloseEvent e;

        dispatcher->Post<WindowCloseEvent>(e);
      });

    // glfwSetWindowCloseCallback(m_Window->GetGLFWWindowPointer(), Application::Hi);

    m_Dispatcher->Subscribe(
      WindowResize,
      FORWARD_CALLBACK_FUNCTION(Application::ResizeWindow, WindowResizeEvent));

    glfwSetWindowSizeCallback(m_Window->GetGLFWWindowPointer(),
                              [](GLFWwindow *windowGLFW, int width, int height) {
                                auto *dispatcher =
                                    static_cast<EventDispatcher *>(glfwGetWindowUserPointer(
                                      windowGLFW));

                                WindowResizeEvent e(width, height);

                                dispatcher->Post<WindowResizeEvent>(e);
                              });

    //   m_Dispatcher->Subscribe(
    //     FramebufferResize,
    //     FORWARD_CALLBACK_FUNCTION(Application::ResizeFramebuffer, FramebufferResizeEvent));
    //
    //   glfwSetFramebufferSizeCallback(m_Window->GetGLFWWindowPointer(),
    //                                  [](GLFWwindow *windowGLFW, int width, int height) {
    //                                    auto *dispatcher =
    //                                        static_cast<EventDispatcher *>(glfwGetWindowUserPointer(
    //                                          windowGLFW));
    //
    //                                    FramebufferResizeEvent e(width, height);
    //
    //                                    dispatcher->Post<FramebufferResizeEvent>(e);
    //                                  });
  }

  Application::~Application() {
    std::cout << "Application destroyed" << std::endl;
  }

  void Application::Run() {
    std::cout << "Application running" << std::endl;

    // Renderer::Init(m_Window->GetGLFWWindowPointer());
    // glViewport(0, 0, 800, 600);


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    int width, height;
    glfwGetFramebufferSize(m_Window->GetGLFWWindowPointer(), &width, &height);


    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_ViewportWidth), static_cast<float>(m_ViewportHeight),
                                      0.0f, -1.0f, 1.0f);

    AssetManager::GetShader("sprite")->use();
    AssetManager::GetShader("sprite")->setUniformi("image", 0);
    AssetManager::GetShader("sprite")->setUniformMat4("projection", projection);

    Gui g(m_Window->GetGLFWWindowPointer());
    LevelEditor l([this]() {
      this->RenderScene();
    }, m_ViewportWidth, m_ViewportHeight);

    bool show_another_window = true;
    bool f = true;
    Renderer::SetClearColour(0.2f, 0.3f, 0.3f, 1.0f);

    while (m_running) {
      auto currentFrame = static_cast<float>(glfwGetTime());
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      g.Start(&show_another_window);

      l.Render();
      ImGui::ShowDemoWindow();


      g.Render();


      UpdateScene(deltaTime);

      m_Window->Update(m_running);
    }
  }

  void Application::Close(WindowCloseEvent &e) {
    m_Window.reset();
    m_running = false;

    AssetManager::Terminate();

    std::cout << "Application closed" << std::endl;
  }

  void Application::ResizeWindow(WindowResizeEvent &e) {
    // Renderer::SetViewport(e.GetWidth(), e.GetHeight());

    // std::cout << "Window resized" << std::endl;
  }

  void Application::ResizeFramebuffer(FramebufferResizeEvent &e) {
    Renderer::SetViewport(e.GetWidth(), e.GetHeight());

    std::cout << "Framebuffer resized" << std::endl;
  }


  void Application::AddGameObject(GameObject &gameObject) {
    m_GameObjects[gameObject.GetID()] = &gameObject;
  }

  void Application::RemoveGameObject(const int ID) {
    m_GameObjects.erase(ID);
  }

  void Application::RenderScene() const {
    for (const auto &pair: m_GameObjects) {
      pair.second->Draw();
    }
  }

  void Application::UpdateScene(float deltaTime) const {
    for (const auto &pair: m_GameObjects) {
      pair.second->OnUpdate(deltaTime);
    }
  }
} // namespace Hamster
