#include "AssetManager.h"

namespace Hamster {
	void AssetManager::AddShader(std::string name, Shader shader) {
		//m_Shaders[name] = shader;
		m_Shaders.emplace(name, shader);
	}

	Shader* AssetManager::GetShader(std::string name) {
		return &m_Shaders.at(name);
	}

	void AssetManager::AddTexture(std::string name, Texture texture) {
		//m_Shaders[name] = shader;
		m_Textures.emplace(name, texture);
	}

	Texture* AssetManager::GetTexture(std::string name) {
		return &m_Textures.at(name);
	}
}