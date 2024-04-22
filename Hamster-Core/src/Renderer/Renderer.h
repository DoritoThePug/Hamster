#pragma once

#include <stdint.h>

#include <glm.hpp>

#include "Shader.h"
#include "Texture.h"

namespace Hamster {
	class Renderer
	{
	public:
		static void Init(uint16_t windowWidth, uint16_t windowHeight);
		static void Terminate();
		static void SetViewport(uint16_t width, uint16_t height);

		static void Clear();
		static void SetClearColour(float r, float g, float b, float a);

		static void DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour);

	private:
		static void InitRendererData();

		inline static Shader* m_Shader;
		inline static unsigned int m_VAO;
	} ;
}
