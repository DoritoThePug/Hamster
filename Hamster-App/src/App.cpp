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

    Player p(app, "face", glm::vec2(500.0f, 500.0f), glm::vec2(300.0f, 300.0f),
             0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    app->Run();

    delete app;
}
