#pragma once

#include <map>
#include <string>

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Hamster {
	class AssetManager
	{
	public:
		static void AddShader(std::string name, Shader shader);
		static Shader* GetShader(std::string name);

		static void AddTexture(std::string name, Texture texture);
		static Texture* GetTexture(std::string name);
	private:
		inline static std::map<std::string, Shader> m_Shaders;
		inline static std::map<std::string, Texture> m_Textures;
	};
}

