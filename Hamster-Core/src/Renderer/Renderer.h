#pragma once

#include <stdint.h>
#include <memory>

#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "GLFW/glfw3.h"

#include "Core/Application.h"

namespace Hamster {
	enum TransformType {
		Translate, Rotate, Scale
	};

	class Renderer {
	public:
		static void Init(int viewportHeight, int viewportWidt);

		static void Terminate();

		static void SetViewport(uint16_t width, uint16_t height);

		static void Clear();

		static void SetClearColour(float r, float g, float b, float a);

		static void DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour);

		static void DrawFlat(glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 colour);

		static void DrawGuizmo(Transform targetTransform, TransformType type, bool selectionColour);

	private:
		static void InitRendererData();

		inline static std::shared_ptr<Shader> m_SpriteShader;
		inline static std::shared_ptr<Shader> m_FlatShader;
		inline static unsigned int m_VAO;
	};
}
