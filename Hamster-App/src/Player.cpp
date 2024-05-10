#include "Player.h"


#include <iostream>
Player::Player(Hamster::Application* app, Hamster::Texture* texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour) :
	GameObject(app, texture, position, size, rotation, colour) {}

Player::Player(Hamster::Application* app) : GameObject(app) {}

void Player::OnUpdate(float deltaTime) {
	//SetPosition(GetPosition() + glm::vec2(1, 0));
}