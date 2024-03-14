#include <iostream>

#include "Core/Application.h"

int main()
{
	Hamster::Application* app = new Hamster::Application();

	app->Run();

	std::cin.get();

	app->Close();

	delete app;
}