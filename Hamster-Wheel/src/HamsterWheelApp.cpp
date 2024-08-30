//
// Created by Jaden on 24/08/2024.
//

#include <Hamster.h>

#include <EditorLayer.h>
#include <fstream>
#include <Core/Scene.h>
#include <Physics/Physics.h>
#include <Core/UUID.h>
#include <Core/SceneSerialiser.h>

int main() {
  auto* app = new Hamster::Application();

    // auto* scene = new Hamster::Scene();

  std::shared_ptr<Hamster::Scene> scene = std::make_shared<Hamster::Scene>();
  



  std:: ifstream file;
  file.open("hi.hs", std::ios::binary);

  Hamster::SceneSerialiser deserialiser(scene);

  deserialiser.Deserialise(file);
  file.close();

  app->AddScene(scene);
  app->SetSceneActive(scene->GetUUID());

  app->PushLayer(new EditorLayer(scene));

//   Hamster::AssetManager::AddTexture(
//        "mario",
//        "C:/Users/Jaden/Documents/DevStuff/Hamster/Hamster-App/Assets/mario-sprite.png");
//
//     Hamster::UUID mario = scene->CreateEntity();
// scene->AddEntityComponent<Hamster::Transform>(mario, glm::vec2(400.0f, 0.0f), 0.0f, glm::vec2(300.0f, 300.0f));
//   scene->AddEntityComponent<Hamster::Sprite>(mario, "mario", Hamster::AssetManager::GetTexture("mario"),
//   glm::vec3(1.0f, 1.0f, 1.0f));
//   scene->AddEntityComponent<Hamster::Name>(mario, "Mario");
//   Hamster::Physics::CreateBody(scene->GetWorldId(), b2_dynamicBody, scene->GetEntity(mario), scene->GetRegistry());

  // auto face = app->GetRegistry().create();
  //
  // app->GetRegistry().emplace<Hamster::Sprite>(face, Hamster::AssetManager::GetTexture("face"),
  //                                             glm::vec3(1.0f, 1.0f, 1.0f));
  // app->GetRegistry().emplace<Hamster::Transform>(face, glm::vec2(400.0f, 0.0f), 0.0f, glm::vec2(300.0f, 300.0f));
  //   app->GetRegistry().emplace<Hamster::Name>(face, "Face0");
  //
  // Hamster::Physics::CreateBody(b2_dynamicBody, face, app->GetRegistry());
  //
  // auto face1 = app->GetRegistry().create();
  //
  // app->GetRegistry().emplace<Hamster::Sprite>(face1, Hamster::AssetManager::GetTexture("face"),
  //                                             glm::vec3(1.0f, 1.0f, 1.0f));
  // app->GetRegistry().emplace<Hamster::Transform>(face1, glm::vec2(100.0f, 900.0f), 0.0f, glm::vec2(1920.0f, 300.0f));
  // app->GetRegistry().emplace<Hamster::Name>(face1, "Face1");
  //
  // Hamster::Physics::CreateBody(b2_staticBody, face1, app->GetRegistry());
  //
  //   // for (int i = 0 ; i < 300 ; i++) {
  //   //   auto face = app->GetRegistry().create();
  //   //
  //   //   app->GetRegistry().emplace<Hamster::Sprite>(face, Hamster::AssetManager::GetTexture("face"),
  //   //                                               glm::vec3(0.0f, 1.0f, 0.0f));
  //   //   app->GetRegistry().emplace<Hamster::Transform>(face, glm::vec2(i*5.0f, 5.0f), 0.0f, glm::vec2(5.0f, 5.0f));
  //   //     app->GetRegistry().emplace<Hamster::Name>(face, "Face" + std::to_string(i));
  //   // }



  app->Run();
  //
  //
  // std::shared_ptr<Hamster::Scene> scene2 = std::make_shared<Hamster::Scene>();
  //
  //
  //
  // std:: ifstream file;
  // file.open("hi.hs", std::ios::binary);
  //
  // Hamster::SceneSerialiser deserialiser(scene);
  //
  // deserialiser.Deserialise(file);
  // file.close();
  //
  delete app;
}
