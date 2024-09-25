#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "Events/Event.h"
#include "Events/WindowEvents.h"
#include "LayerStack.h"
#include "Log.h"
#include "Window.h"

#include "Gui/ImGuiLayer.h"
#include "Renderer/Texture.h"
#include "Scene.h"
#include "Utils/InputManager.h"

namespace Hamster {
class Application {
public:
  Application();

  ~Application();

  void Run();

  void Close(WindowCloseEvent &e);

  glm::mat4 GetProjectionMatrix();

  std::shared_ptr<EventDispatcher> GetEventDispatcher() { return m_Dispatcher; }

  static Application &GetApplicationInstance() { return *s_Instance; }

  static void ResizeWindow(WindowResizeEvent &e);

  void ResizeFramebuffer(FramebufferResizeEvent &e);

  void PauseSimulation();

  void ResumeSimulation();

  bool IsSimulationPaused();

  GLFWwindow *GetWindow() { return m_Window->GetGLFWWindowPointer(); }

  void PushLayer(Layer *layer);

  void PopLayer(Layer *layer);

  [[nodiscard]] int GetViewportHeight() const { return m_ViewportHeight; }
  [[nodiscard]] int GetViewportWidth() const { return m_ViewportWidth; }

  void SetViewportHeight(const int height) { m_ViewportHeight = height; }
  void SetViewportWidth(const int width) { m_ViewportWidth = width; }

  static glm::vec3 IdToColour(int id);

  static int ColourToId(glm::vec3 colour);

  void AddScene(std::shared_ptr<Scene> scene);

  void RemoveScene(UUID uuid);

  void RemoveAllScenes();

  void StopActiveScene();

  void SetSceneActive(UUID uuid);

  std::shared_ptr<Scene> GetScene(UUID uuid);

  std::shared_ptr<Scene> GetActiveScene();

private:
  static Application *s_Instance;

  bool m_Running = true;
  bool m_IsSimulationPaused = true;

  int m_ViewportWidth = 1920;
  int m_ViewportHeight = 1080;

  glm::mat4 m_Projection;

  std::shared_ptr<EventDispatcher> m_Dispatcher;
  LayerStack m_LayerStack;

  ImGuiLayer m_ImGuiLayer;

  std::unique_ptr<Window> m_Window;

  std::unique_ptr<InputManager> m_InputManager;

  std::unordered_map<UUID, std::shared_ptr<Scene>> m_Scenes;
  std::shared_ptr<Scene> m_ActiveScene = nullptr;

  WindowProps m_WindowProps;
};
} // namespace Hamster
