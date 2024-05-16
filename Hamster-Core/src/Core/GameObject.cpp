#include "GameObject.h"

#include "Renderer/Renderer.h"
//#include "Events/Event.h"
#include "Utils/AssetManager.h"
#include "Core/Application.h"
//#include "Events/ApplicationEvents.h"

namespace Hamster {
	GameObject::GameObject(Application* app, std::string textureName, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour)
		: m_SpriteTexture(textureName), m_Position(position), m_Size(size), m_Rotation(rotation), m_SpriteColour(colour) {
		m_ID = s_CurrentID += 1;

		app->AddGameObject(*this);
	}

	void GameObject::Draw() {
		Renderer::DrawSprite(*AssetManager::GetTexture(m_SpriteTexture), m_Position, m_Size, m_Rotation, m_SpriteColour);
	}

	//Setters
	void GameObject::SetSprite(std::string textureName) {
		m_SpriteTexture = textureName;
	}

	void GameObject::SetPosition(glm::vec2 position) {
		m_Position = position;
	}

	void GameObject::SetSize(glm::vec2 size) {
		m_Size = size;
	}

	void GameObject::SetRotation(float rotation) {
		m_Rotation = rotation;
	}

	void GameObject::SetColour(glm::vec3 colour) {
		m_SpriteColour = colour;
	}

	//Getters
	std::string GameObject::GetSprite() const {
		return m_SpriteTexture;
	}

	glm::vec2 GameObject::GetPosition() const {
		return m_Position;
	}

	glm::vec2 GameObject::GetSize() const {
		return m_Size;
	}

	float GameObject::GetRotation() const {
		return m_Rotation;
	}

	glm::vec3 GameObject::GetColour() const {
		return m_SpriteColour;
	}

	int GameObject::GetID() const {
		return m_ID;
	}
}