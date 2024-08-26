#include "Texture.h"

#include <iostream>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

#include "Utils/AssetManager.h"

namespace Hamster {
	Texture::Texture(const char* texturePath) {
		int width, height, nrChannels;

		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, STBI_rgb_alpha);

		if (!data) {
			std::cout << "Texture could not be loaded" << std::endl;
		}

		glGenTextures(1, &m_ID);

		glBindTexture(GL_TEXTURE_2D, m_ID);

		int imageFormat;

		if (nrChannels == 3) {
			imageFormat = GL_RGB;
		}
		else if (nrChannels == 4) {
			imageFormat = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);


		stbi_image_free(data);
	}

	void Texture::BindTexture() {
		//std::cout << "Hi" << std::endl;

		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}