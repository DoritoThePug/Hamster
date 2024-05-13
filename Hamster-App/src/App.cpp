#include <iostream>
#include <memory>

#include "Core/Application.h"
#include "Utils/AssetManager.h"
#include "Renderer/Texture.h"
//#include "Events/Event.h"

#include "Player.h"

//static Hamster::Application* app;

int main()
{
	Hamster::Application* app = new Hamster::Application();

	std::shared_ptr<Hamster::Texture> face = Hamster::AssetManager::AddTexture("face", "C:/Users/jaden/OneDrive/Documents/Hamster/Hamster/Hamster-App/Assets/awesomeface.png");
	//Hamster::AssetManager::AddTexture("face", face);

	Player p(app, face.get(), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	app->Run();

	std::cin.get();

	delete app;
}