#include "Player.h"


#include <iostream>
//Player::Player(Hamster::Texture* texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour, Hamster::Application& app) : 
//	GameObject(app, texture, position, size, rotation, colour) {}

Player::Player(Hamster::Application* app) : GameObject(app) {}

void Player::OnUpdate() {
	std::cout << "Hi" << std::endl;
}