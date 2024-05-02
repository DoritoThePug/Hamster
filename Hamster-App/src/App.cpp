#include <iostream>

#include "Core/Application.h"
#include "Utils/AssetManager.h"
//#include "Events/Event.h"

#include "Player.h"

//static Hamster::Application* app;

int main()
{
	Hamster::Application* app = new Hamster::Application();

	//Player p(app);

	Hamster::Texture* face = new Hamster::Texture("C:/Users/jaden/awesomeface.png");
	//Hamster::AssetManager::AddTexture("face", *face);

	Player p(app, face, glm::vec2(200.0f, 200.0f), glm::vec2(10.0f, 10.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	app->Run();

	std::cin.get();

	delete face;
	delete app;
}