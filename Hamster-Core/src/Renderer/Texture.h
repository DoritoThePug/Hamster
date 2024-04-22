#pragma once

#include <string>

namespace Hamster {
	/*struct TextureData {
		uint8_t id;

		uint16_t width, height;

		uint8_t sourceFormat;

		uint8_t verticalWrap, horizontalWrap;

		TextureData(uint8_t id, uint16_t width, uint16_t height, uint16_t format, uint8_t verticalWrap, uint8_t horizontalWrap) :
			id(id), width(width), height(height), sourceFormat(format), verticalWrap(verticalWrap), horizontalWrap(horizontalWrap) {};
	};*/

	/*enum ImageFromat {
		RGB,
		RGBA
	};*/

	class Texture
	{
	public:
		Texture(const char* texturePath);

		void BindTexture();
	private:
		/*TextureData m_TextureData;*/
		unsigned int m_ID;
	};
}

