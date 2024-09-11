#include "AssetManager.h"

namespace Hamster {
  std::shared_ptr<Shader>
  AssetManager::AddShader(std::string name, const std::string &vertexShaderPath,
                          const std::string &fragmentShaderPath) {
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(
      vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    // m_Shaders.emplace(name, shader);

    m_Shaders[name] = shader;

    return shader;
  }

  std::shared_ptr<Shader> AssetManager::GetShader(std::string name) {
    if (name != "") {
      return m_Shaders.at(name);
    } else {
      return nullptr;
    }
  }

  void AssetManager::AddTexture(const std::string &texturePath) {
    std::cout << "Add texture with path " << texturePath << std::endl;

    std::shared_ptr<Texture> texture =
        std::make_shared<Texture>(texturePath.c_str());

    m_Textures.emplace(texture->GetUUID(), texture);
  }

  void AssetManager::AddTexture(UUID uuid, const std::string &texturePath,
                                const std::string &textureName) {
    std::shared_ptr<Texture> texture =
        std::make_shared<Texture>(texturePath.c_str());

    texture->SetUUID(uuid);
    texture->SetName(textureName);

    m_Textures.emplace(uuid, texture);

    for (const auto &[uuid, texture]: m_Textures) {
      std::cout << uuid.GetUUID() << " here" << std::endl;
    }
  }

  std::shared_ptr<Texture> AssetManager::GetTexture(UUID uuid) {
    return m_Textures.at(uuid);
  }

  UUID AssetManager::AddScript(const std::filesystem::path &scriptPath,
                               const std::string &fileName) {
    std::shared_ptr<HamsterScript> script =
        std::make_shared<HamsterScript>(scriptPath, fileName);

    m_Scripts.emplace(script->GetUUID(), script);

    return script->GetUUID();
  }

  void AssetManager::AddScript(UUID uuid, const std::filesystem::path &scriptPath,
                               const std::string &fileName,
                               const std::string &scriptName) {
    std::shared_ptr<HamsterScript> script =
        std::make_shared<HamsterScript>(scriptPath, fileName);

    script->SetUUID(uuid);
    script->SetName(scriptName);

    m_Scripts.emplace(uuid, script);
  }

  std::shared_ptr<HamsterScript> AssetManager::GetScript(UUID uuid) {
    return m_Scripts.at(uuid);
  }


  void AssetManager::Terminate() {
    m_Textures.clear();
    m_Shaders.clear();
  }
} // namespace Hamster
