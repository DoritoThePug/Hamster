#pragma once

#include <stdint.h>
#include <memory>

#include <glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "GLFW/glfw3.h"

namespace Hamster {
	class Renderer {
	public:
		static void Init(int viewportHeight, int viewportWidt);

		static void Terminate();

		static void SetViewport(uint16_t width, uint16_t height);

		static void Clear();

		static void SetClearColour(float r, float g, float b, float a);

		static void DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour);

	private:
		static void InitRendererData();

		inline static std::shared_ptr<Shader> m_Shader;
		inline static unsigned int m_VAO;
	};
}
