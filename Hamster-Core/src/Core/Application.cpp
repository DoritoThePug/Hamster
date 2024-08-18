#include <iostream>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
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

    InputManager inputManager(m_Window->GetGLFWWindowPointer());

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_ViewportWidth), static_cast<float>(m_ViewportHeight),
                                      0.0f, -1.0f, 1.0f);

    AssetManager::GetShader("sprite")->use();
    AssetManager::GetShader("sprite")->setUniformi("image", 0);
    AssetManager::GetShader("sprite")->setUniformMat4("projection", projection);

    AssetManager::GetShader("flat")->use();
    AssetManager::GetShader("flat")->setUniformi("image", 0);
    AssetManager::GetShader("flat")->setUniformMat4("projection", projection);

    Gui g(m_Window->GetGLFWWindowPointer());
    LevelEditor l([this](bool renderFlat) {
                    this->RenderSystem(m_Registry, renderFlat);
                  }, m_ViewportWidth,
                  m_ViewportHeight,
                  m_Window->GetGLFWWindowPointer());

    bool show_another_window = true;
    bool f = true;
    Renderer::SetClearColour(0.2f, 0.3f, 0.3f, 1.0f);

    // layer p(app, "face", glm::vec2(500.0f, 500.0f), glm::vec2(300.0f, 300.0f),
    //          0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (m_running) {
      auto currentFrame = static_cast<float>(glfwGetTime());
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;


      g.Start(&show_another_window);

      // ImGui::GetWindowPos();

      l.Render();
      ImGui::ShowDemoWindow();


      g.Render();


      // UpdateScene(deltaTime);

      UpdateSystem(m_Registry);

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

  void Application::UpdateSystem(entt::registry &registry) {
    auto view = registry.view<Transform>();

    view.each([](auto &transform) {
      // transform.position = transform.position + glm::vec2(1.0f, 0.0f);
    });
  }

  void Application::RenderSystem(entt::registry &registry, bool renderFlat) {
    auto view = registry.view<Sprite, Transform>();

    if (!renderFlat) {
      view.each([](auto &sprite, auto &transform) {
        Renderer::DrawSprite(*sprite.texture, transform.position, transform.size, transform.rotation, sprite.colour);
      });
    } else {
      // render all sprites as a unique flat colour which can be used to identify to their id

      // std::cout << "hi" << std::endl;

      view.each([](auto entity, auto &sprite, auto &transform) {
        int id = entt::to_integral(entity) + 1;
        // +1 to ensure no ids are 0 as an invalid coordinate causes opengl to return 0 on read pixel
        int r = (id & 0x000000FF) >> 0;
        int g = (id & 0x0000FF00) >> 8;
        int b = (id & 0x00FF0000) >> 16;

        // std::cout << r / 255.0f << std::endl;

        Renderer::DrawFlat(transform.position, transform.size, transform.rotation,
                           glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
      });
    }
  }
} // namespace Hamster
