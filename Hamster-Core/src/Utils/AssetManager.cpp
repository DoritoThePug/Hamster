#include "AssetManager.h"

namespace Hamster {
	std::shared_ptr<Shader> AssetManager::AddShader(std::string name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

		//m_Shaders.emplace(name, shader);

		m_Shaders[name] = shader;

		return shader;
	}

	std::shared_ptr<Shader> AssetManager::GetShader(std::string name) {
		if (name != "") {
			return m_Shaders.at(name);
		}
		else {
			return nullptr;
		}
	}

	void AssetManager::AddTexture(std::string name, const std::string& texturePath) {
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(texturePath.c_str());
		
		m_Textures.emplace(name, texture);
	}

	std::shared_ptr<Texture> AssetManager::GetTexture(std::string name) {
		if (name != "") {
			return m_Textures.at(name);
		}
		else {
			return nullptr;
		}
	}


	void AssetManager::Terminate() {
		m_Textures.clear();
		m_Shaders.clear();
	}
}