#pragma once

#include <stdint.h>

namespace Hamster {
	class Renderer
	{
	public:
		static void Init(uint16_t windowWidth, uint16_t windowHeight);
		static void Terminate();
		static void SetViewport(uint16_t width, uint16_t height);

		static void Clear();
		static void SetClearColour(float r, float g, float b, float a);
	};
}
