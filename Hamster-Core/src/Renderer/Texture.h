#pragma once

#include <iostream>
#include <ostream>
#include <string>

namespace Hamster {
	class Texture {
	public:
		Texture(const std::string& texturePath);

		void BindTexture();

		[[nodiscard]] const std::string& GetTexturePath() const {
			return m_TexturePath;
		}
	private:
		unsigned int m_ID;
		const std::string m_TexturePath;
	};
}

