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

#include "ProjectHubLayer.h"

int main() {
    auto *app = new Hamster::Application();

    EditorLayer *editorLayer;
    ProjectHubLayer *projectHubLayer = new ProjectHubLayer(editorLayer);


    app->PushLayer(projectHubLayer);

    // app->PushLayer(new EditorLayer(scene));

    Hamster::AssetManager::AddTexture(
        "mario",
        "C:/Users/Jaden/Documents/DevStuff/Hamster/Hamster-App/Assets/mario-sprite.png");
    //
    // Hamster::UUID mario = scene->CreateEntity();
    // scene->AddEntityComponent<Hamster::Transform>(mario, glm::vec2(400.0f, 0.0f), 0.0f, glm::vec2(300.0f, 300.0f));
    // scene->AddEntityComponent<Hamster::Sprite>(mario, "mario", Hamster::AssetManager::GetTexture("mario"),
    //                                            glm::vec3(1.0f, 1.0f, 1.0f));
    // scene->AddEntityComponent<Hamster::Name>(mario, "Mario");
    // Hamster::Physics::CreateBody(scene->GetWorldId(), b2_dynamicBody, scene->GetEntity(mario), scene->GetRegistry());

    app->Run();

    delete app;
}
