#include "HamsterPCH.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include "Application.h"

#include "Base.h"
#include "Events/ApplicationEvents.h"
#include "Layer.h"
#include "Physics/Physics.h"
#include "Project.h"
#include "Renderer/FramebufferTexture.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Scripting/Scripting.h"
#include "Utils/AssetManager.h"

namespace Hamster {
// Singleton was chosen due to need for all systems to access the Application
// class + there should only ever be 1 instance of Application even when
// Hamster-Wheel is running
Application *Application::s_Instance = nullptr;

Application::Application() {
  std::cout << "Application created" << std::endl;

  s_Instance = this;

  Log::Init();

  // Similarly, only 1 window is needed, ImGui can handle "sub-windows"
  m_Window = std::make_unique<Window>(m_WindowProps);

  m_InputManager =
      std::make_unique<InputManager>(m_Window->GetGLFWWindowPointer());

  Renderer::Init(m_ViewportHeight, m_ViewportWidth);

  // Global dispatcher for all events, aren't many events posted, may create a
  // dispatcher for user use serperate from internal use
  m_Dispatcher = std::make_shared<EventDispatcher>();

  PushLayer(&m_ImGuiLayer);

  m_Window->SetWindowEventDispatcher(m_Dispatcher.get());

  m_Dispatcher->Subscribe(
      WindowClose,
      FORWARD_CALLBACK_FUNCTION(Application::Close, WindowCloseEvent));

  glfwSetWindowCloseCallback(
      m_Window->GetGLFWWindowPointer(), [](GLFWwindow *windowGLFW) {
        auto *dispatcher = static_cast<EventDispatcher *>(
            glfwGetWindowUserPointer(windowGLFW));

        WindowCloseEvent e;

        dispatcher->Post<WindowCloseEvent>(e);
      });

  // glfwSetWindowSizeCallback(m_Window->GetGLFWWindowPointer(),
  //                           [](GLFWwindow *windowGLFW, int width, int height)
  //                           {
  //                             auto *dispatcher =
  //                                 static_cast<EventDispatcher
  //                                 *>(glfwGetWindowUserPointer(
  //                                   windowGLFW));
  //
  //                             WindowResizeEvent e(width, height);
  //
  //                             dispatcher->Post<WindowResizeEvent>(e);
  //
  //                             std::cout << "window size " << width << ", "
  //                                       << height << std::endl;
  //                           });

  // Use of framebuffer resize to support high DPI displays + Linux framebuffer
  // size and window size do not match unlike on Window, window resize callback
  // commented above incase needed for gui resizing
  m_Dispatcher->Subscribe(FramebufferResize, FORWARD_CALLBACK_FUNCTION(
                                                 Application::ResizeFramebuffer,
                                                 FramebufferResizeEvent));

  glfwSetFramebufferSizeCallback(
      m_Window->GetGLFWWindowPointer(),
      [](GLFWwindow *windowGLFW, int width, int height) {
        auto *dispatcher = static_cast<EventDispatcher *>(
            glfwGetWindowUserPointer(windowGLFW));

        FramebufferResizeEvent e(width, height);

        dispatcher->Post<FramebufferResizeEvent>(e);
      });
}

Application::~Application() {
  // Most cleanup is actually handled by window closing rather than Application
  // being destroyed due to designed destruction order
  std::cout << "Application destroyed" << std::endl;
}

void Application::Run() {
  std::cout << "Application running" << std::endl;

  // Variables left for deltatime calculations, will move later to scene so can
  // be passed to scripts
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  // Only 2 shaders used, one for rendering sprites and one for rendering flat
  // colours used in selection

  m_Projection =
      glm::ortho(0.0f, static_cast<float>(m_ViewportWidth),
                 static_cast<float>(m_ViewportHeight), 0.0f, -1.0f, 1.0f);

  AssetManager::GetShader("sprite")->use();
  AssetManager::GetShader("sprite")->setUniformi("image", 0);
  AssetManager::GetShader("sprite")->setUniformMat4("projection", m_Projection);

  AssetManager::GetShader("flat")->use();
  AssetManager::GetShader("flat")->setUniformi("image", 0);
  AssetManager::GetShader("flat")->setUniformMat4("projection", m_Projection);

  Renderer::SetClearColour(0.0f, 0.0f, 0.0f, 1.0f);

  while (m_Running) {
    // Delta time calculations
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Normal layers updated before gui so gui can respond to changes
    for (Layer *layer : m_LayerStack) {
      layer->OnUpdate();
    }

    m_ImGuiLayer.Begin();

    for (Layer *layer : m_LayerStack) {
      layer->OnImGuiUpdate();
    }

    m_ImGuiLayer.End();

    if (m_ActiveScene != nullptr) {
      m_ActiveScene->OnUpdate();
    }

    m_Window->Update(m_Running);
  }
}

void Application::Close(WindowCloseEvent &e) {
  m_Running = false;
  m_Window.reset();

  Project::SaveCurrentProject();

  for (auto const &[uuid, scene] : m_Scenes) {
    std::cout << "Currently saving scene with uuid: " << uuid.GetUUID()
              << std::endl;
    Scene::SaveScene(scene);
  }

  AssetManager::Terminate();

  std::cout << "Application closed" << std::endl;
}

void Application::ResizeWindow(WindowResizeEvent &e) {
  // Renderer::SetViewport(e.GetWidth(), e.GetHeight());

  // m_Projection =

  // std::cout << "Window resized" << std::endl;
}

void Application::ResizeFramebuffer(FramebufferResizeEvent &e) {
  m_ViewportHeight = e.GetHeight();
  m_ViewportWidth = e.GetWidth();

  Renderer::SetViewport(e.GetWidth(), e.GetHeight());

  // Projection matrix adjusted to account for aspect ratio changes to avoid
  // distortion in rendering
  m_Projection =
      glm::ortho(0.0f, static_cast<float>(m_ViewportWidth),
                 static_cast<float>(m_ViewportHeight), 0.0f, -1.0f, 1.0f);

  AssetManager::GetShader("sprite")->use();
  AssetManager::GetShader("sprite")->setUniformi("image", 0);
  AssetManager::GetShader("sprite")->setUniformMat4("projection", m_Projection);

  AssetManager::GetShader("flat")->use();
  AssetManager::GetShader("flat")->setUniformi("image", 0);
  AssetManager::GetShader("flat")->setUniformMat4("projection", m_Projection);
}

void Application::PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }

void Application::PopLayer(Layer *layer) { m_LayerStack.PopLayer(layer); }

glm::mat4 Application::GetProjectionMatrix() { return m_Projection; }

glm::vec3 Application::IdToColour(int id) {
  // Used to convert an entity handle to a colour, 1 is added to the handle so
  // that 0 is an invalid id; OpenGL returns 0 as the colour for an invalid
  // pixel selection

  id += 1;

  int r = (id & 0x000000FF) >> 0;
  int g = (id & 0x0000FF00) >> 8;
  int b = (id & 0x00FF0000) >> 16;

  return {r / 255.0f, g / 255.0f, b / 255.0f};
}

int Application::ColourToId(const glm::vec3 colour) {
  // Converts colour back to an entity handle used in ECS, 1 is subtracted to
  // account for invalid id

  int id = static_cast<int>(colour.r) << 0 | static_cast<int>(colour.g) << 8 |
           static_cast<int>(colour.b) << 16;

  return id - 1;
}

void Application::PauseSimulation() { m_IsSimulationPaused = true; }

void Application::ResumeSimulation() { m_IsSimulationPaused = false; }

bool Application::IsSimulationPaused() { return m_IsSimulationPaused; }

void Application::AddScene(std::shared_ptr<Scene> scene) {
  m_Scenes[scene->GetUUID()] = scene;
}

void Application::RemoveScene(UUID uuid) { m_Scenes.erase(uuid); }

void Application::RemoveAllScenes() {
  // Used for resetting application to load new project

  m_ActiveScene = nullptr;
  m_Scenes.clear();
}

void Application::StopActiveScene() {
  // Pauses running of active scene for loading in new scene or serialisation of
  // current scene

  if (m_ActiveScene != nullptr) {
    m_ActiveScene->PauseScene();
    m_ActiveScene->PauseSceneSimulation();
  }
}

void Application::SetSceneActive(UUID uuid) {
  // Sets a scene as active, each application can only have 1 active scene, the
  // active scene will be the scene that is rendered on screen

  if (m_ActiveScene != nullptr) {
    m_ActiveScene->PauseScene();
    m_ActiveScene->PauseSceneSimulation();
  }

  std::shared_ptr<Scene> scene = m_Scenes[uuid];

  if (scene) {
    m_ActiveScene = scene;

    ActiveSceneChangedEvent e(m_ActiveScene);

    m_Dispatcher->Post<ActiveSceneChangedEvent>(e);

    m_ActiveScene->RunScene();

    std::cout << scene->GetUUID().GetUUIDString() << std::endl;
  } else {
    std::cout << "Scene not found" << std::endl;

    m_ActiveScene = nullptr;
  }
}

std::shared_ptr<Scene> Application::GetScene(UUID uuid) {
  return m_Scenes[uuid];
}

std::shared_ptr<Scene> Application::GetActiveScene() { return m_ActiveScene; }
} // namespace Hamster
