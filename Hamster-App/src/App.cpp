#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>


#include "Core/Application.h"
#include "Renderer/Texture.h"
#include "Utils/AssetManager.h"
// #include "Events/Event.h"

#include "Player.h"

// static Hamster::Application* app;

int main() {
    Hamster::Application *app = new Hamster::Application();

    Hamster::AssetManager::AddTexture(
        "face",
        "/home/jaden/Documents/dev/Hamster/Hamster-App/Assets/awesomeface.png");

    auto face = app->GetRegistry().create();

    app->GetRegistry().emplace<Hamster::Sprite>(face, Hamster::AssetManager::GetTexture("face"),
                                                glm::vec3(0.0f, 1.0f, 0.0f));
    app->GetRegistry().emplace<Hamster::Transform>(face, glm::vec2(1620.0f, 780.0f), 0.0f, glm::vec2(300.0f, 300.0f));

    auto face1 = app->GetRegistry().create();

    app->GetRegistry().emplace<Hamster::Sprite>(face1, Hamster::AssetManager::GetTexture("face"),
                                                glm::vec3(0.0f, 1.0f, 0.0f));
    app->GetRegistry().emplace<Hamster::Transform>(face1, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(300.0f, 300.0f));

    auto face2 = app->GetRegistry().create();

    app->GetRegistry().emplace<Hamster::Sprite>(face2, Hamster::AssetManager::GetTexture("face"),
                                                glm::vec3(0.0f, 1.0f, 0.0f));
    app->GetRegistry().emplace<Hamster::Transform>(face2, glm::vec2(0.0f, 780.0f), 0.0f, glm::vec2(300.0f, 300.0f));

    auto face3 = app->GetRegistry().create();

    app->GetRegistry().emplace<Hamster::Sprite>(face3, Hamster::AssetManager::GetTexture("face"),
                                                glm::vec3(0.0f, 1.0f, 0.0f));
    app->GetRegistry().emplace<Hamster::Transform>(face3, glm::vec2(1620.0f, 0.0f), 0.0f, glm::vec2(300.0f, 300.0f));

    // Player p(app, "face", glm::vec2(500.0f, 500.0f), glm::vec2(300.0f, 300.0f),
    //          0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    app->Run();

    delete app;
}
