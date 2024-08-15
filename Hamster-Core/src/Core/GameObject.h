#pragma once

#include <memory>
#include <string>

#include <glm.hpp>

#include "Renderer/Texture.h"

namespace Hamster {
	class Application;

	class GameObject {
	public:
		GameObject(Application *app, std::string textureName = "", glm::vec2 position = glm::vec2(0.0f, 0.0f),
		           glm::vec2 size = glm::vec2(100.0f, 100.0f), float rotation = 0.0f,
		           glm::vec3 colour = glm::vec3(255.0f, 255.0f, 255.0f));

		void Draw();

		void SetSprite(std::string textureName);

		void SetPosition(glm::vec2 position);

		void SetSize(glm::vec2 size);

		void SetRotation(float rotation);

		void SetColour(glm::vec3 colour);

		[[nodiscard]] std::string GetSprite() const;

		[[nodiscard]] glm::vec2 GetPosition() const;

		[[nodiscard]] glm::vec2 GetSize() const;

		[[nodiscard]] float GetRotation() const;

		[[nodiscard]] glm::vec3 GetColour() const;

		[[nodiscard]] int GetID() const;

		virtual void OnStart() {
		};

		virtual void OnUpdate(float deltaTime) {
		};

		virtual void OnDestroyed() {
		};

	private:
		std::string m_SpriteTexture;
		glm::vec2 m_Position;
		glm::vec2 m_Size;
		float m_Rotation;
		glm::vec3 m_SpriteColour;
		int m_ID;

		// Keeps track of ID we're on
		inline static int s_CurrentID = 0;
	};
}
