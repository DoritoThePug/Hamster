#pragma once

#include <map>
#include <string>
#include <memory>

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Hamster {
	class AssetManager {
	public:
		static std::shared_ptr<Shader> AddShader(std::string name, const std::string &vertexShaderPath,
		                                         const std::string &fragmentShaderPath);

		static std::shared_ptr<Shader> GetShader(std::string name);

		static void AddTexture(std::string name, const std::string &texturePath);

		static std::shared_ptr<Texture> GetTexture(std::string name);

		static void Terminate();

	private:
		inline static std::map<std::string, std::shared_ptr<Shader> > m_Shaders;
		inline static std::map<std::string, std::shared_ptr<Texture> > m_Textures;
	};
}

