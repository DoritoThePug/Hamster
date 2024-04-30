#pragma once

#include <Core/GameObject.h>
#include <Renderer/Texture.h>
//#include <Events/Event.h>

//#include "App.cpp"


class Player : public Hamster::GameObject
{
public:
	//Player(Hamster::Texture* texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour, Hamster::Application& app);
	Player(Hamster::Application* app);

	void OnUpdate();
};

