//
// Created by Jaden on 24/08/2024.
//

#include <Core/Application.h>
#include <Utils/AssetManager.h>

#include "EditorLayer.h"

int main() {
  auto* app = new Hamster::Application();

  app->PushLayer(new EditorLayer([app](bool renderFlat) {
    app->RenderSystem(app->GetRegistry(), renderFlat);
  }));

  Hamster::AssetManager::AddTexture(
       "face",
       "C:/Users/Jaden/Documents/DevStuff/Hamster/Hamster-App/Assets/awesomeface.png");

  auto face = app->GetRegistry().create();

  app->GetRegistry().emplace<Hamster::Sprite>(face, Hamster::AssetManager::GetTexture("face"),
                                              glm::vec3(0.0f, 1.0f, 0.0f));
  app->GetRegistry().emplace<Hamster::Transform>(face, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(300.0f, 300.0f));

  app->Run();

  delete app;
}