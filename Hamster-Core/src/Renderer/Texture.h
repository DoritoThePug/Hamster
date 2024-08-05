#pragma once

#include <string>

namespace Hamster {
	class Texture {
	public:
		Texture(const char *texturePath);

		void BindTexture();

	private:
		unsigned int m_ID;
	};
}

