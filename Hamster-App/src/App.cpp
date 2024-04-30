#include <iostream>

#include "Core/Application.h"
//#include "Events/Event.h"

#include "Player.h"

//static Hamster::Application* app;

int main()
{
	Hamster::Application* app = new Hamster::Application();

	Player p(app);

	app->Run();

	std::cin.get();

	delete app;
}