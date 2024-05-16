#pragma once

#include <string>

#include <Core/GameObject.h>
#include <Renderer/Texture.h>
//#include <Events/Event.h>

//#include "App.cpp"


class Player : public Hamster::GameObject
{
public:
	Player(Hamster::Application* app, std::string textureName, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour);
	Player(Hamster::Application* app);

	void OnUpdate(float deltaTime) override;
};

