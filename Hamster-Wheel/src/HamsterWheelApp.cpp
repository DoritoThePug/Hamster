//
// Created by Jaden on 24/08/2024.
//

#include <Hamster.h>

#include "EditorLayer.h"
#include "Physics/Physics.h"

int main() {
  auto* app = new Hamster::Application();

  app->PushLayer(new EditorLayer([app](bool renderFlat) {
    app->RenderSystem(app->GetRegistry(), renderFlat);
  }, *app));

  Hamster::AssetManager::AddTexture(
       "face",
       "C:/Users/Jaden/Documents/DevStuff/Hamster/Hamster-App/Assets/awesomeface.png");

  auto face = app->GetRegistry().create();

  app->GetRegistry().emplace<Hamster::Sprite>(face, Hamster::AssetManager::GetTexture("face"),
                                              glm::vec3(1.0f, 1.0f, 1.0f));
  app->GetRegistry().emplace<Hamster::Transform>(face, glm::vec2(400.0f, 0.0f), 0.0f, glm::vec2(300.0f, 300.0f));
    app->GetRegistry().emplace<Hamster::Name>(face, "Face0");

  Hamster::Physics::CreateBody(b2_dynamicBody, face, app->GetRegistry());

  auto face1 = app->GetRegistry().create();

  app->GetRegistry().emplace<Hamster::Sprite>(face1, Hamster::AssetManager::GetTexture("face"),
                                              glm::vec3(1.0f, 1.0f, 1.0f));
  app->GetRegistry().emplace<Hamster::Transform>(face1, glm::vec2(100.0f, 900.0f), 0.0f, glm::vec2(1920.0f, 300.0f));
  app->GetRegistry().emplace<Hamster::Name>(face1, "Face1");

  Hamster::Physics::CreateBody(b2_staticBody, face1, app->GetRegistry());

    // for (int i = 0 ; i < 300 ; i++) {
    //   auto face = app->GetRegistry().create();
    //
    //   app->GetRegistry().emplace<Hamster::Sprite>(face, Hamster::AssetManager::GetTexture("face"),
    //                                               glm::vec3(0.0f, 1.0f, 0.0f));
    //   app->GetRegistry().emplace<Hamster::Transform>(face, glm::vec2(i*5.0f, 5.0f), 0.0f, glm::vec2(5.0f, 5.0f));
    //     app->GetRegistry().emplace<Hamster::Name>(face, "Face" + std::to_string(i));
    // }

  app->Run();

  delete app;
}
