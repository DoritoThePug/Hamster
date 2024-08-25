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
#include "Layer.h"
// #include "Gui/ImGuiLayer.h"

namespace Hamster {
  Application* Application::s_Instance = nullptr;

  Application::Application() {
    std::cout << "Application created" << std::endl;

    s_Instance = this;

    m_Window = std::make_unique<Window>(m_WindowProps);

    Renderer::Init(m_ViewportHeight, m_ViewportWidth);



    m_Dispatcher = std::make_unique<EventDispatcher>();

    PushLayer(&m_ImGuiLayer);

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

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    int width, height;
    glfwGetFramebufferSize(m_Window->GetGLFWWindowPointer(), &width, &height);

    m_Projection = glm::ortho(0.0f, static_cast<float>(m_ViewportWidth), static_cast<float>(m_ViewportHeight),
                                      0.0f, -1.0f, 1.0f);

    AssetManager::GetShader("sprite")->use();
    AssetManager::GetShader("sprite")->setUniformi("image", 0);
    AssetManager::GetShader("sprite")->setUniformMat4("projection", m_Projection);

    AssetManager::GetShader("flat")->use();
    AssetManager::GetShader("flat")->setUniformi("image", 0);
    AssetManager::GetShader("flat")->setUniformMat4("projection", m_Projection);

    Renderer::SetClearColour(0.0f, 0.0f, 0.0f, 0.0f);

    while (m_running) {
      auto currentFrame = static_cast<float>(glfwGetTime());
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      for (Layer* layer : m_LayerStack) {
        layer->OnUpdate();

      }


      m_ImGuiLayer.Begin();

      for (Layer* layer : m_LayerStack) {
        layer->OnImGuiUpdate();
      }

      m_ImGuiLayer.End();

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

        Renderer::DrawFlat(transform.position, transform.size, transform.rotation,
                           IdToColour(entt::to_integral(entity)));
      });
    }
  }

  void Application::PushLayer(Layer *layer) {
    m_LayerStack.PushLayer(layer);
  }

  void Application::PopLayer(Layer *layer) {
    m_LayerStack.PopLayer(layer);
  }

  glm::mat4 Application::GetProjectionMatrix() {
    return m_Projection;
  }

  glm::vec3 Application::IdToColour(int id) {
    id += 1;



    int r = (id & 0x000000FF) >> 0;
    int g = (id & 0x0000FF00) >> 8;
    int b = (id & 0x00FF0000) >> 16;

    return {r / 255.0f, g / 255.0f, b / 255.0f};
  }

  int Application::ColourToId(const glm::vec3 colour) {
    int pickedID =
            (colour.r +
            colour.g * 256 +
            colour.b * 256 * 256)-1;

    return pickedID;
  }
} // namespace Hamster