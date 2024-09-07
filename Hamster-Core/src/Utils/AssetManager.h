#pragma once

#include <map>
#include <memory>
#include <string>

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace Hamster {
class AssetManager {
public:
  static std::shared_ptr<Shader>
  AddShader(std::string name, const std::string &vertexShaderPath,
            const std::string &fragmentShaderPath);

  static std::shared_ptr<Shader> GetShader(std::string name);

  static void AddTexture(UUID uuid, const std::string &texturePath,
                         const std::string &textureName);

  static void AddTexture(const std::string &texturePath);

  static std::shared_ptr<Texture> GetTexture(UUID uuid);

  static const std::unordered_map<UUID, std::shared_ptr<Texture>> &
  GetTextureMap() {
    return m_Textures;
  }

  static uint32_t GetTextureCount() {
    return static_cast<uint32_t>(m_Textures.size());
  }

  static void Terminate();

private:
  inline static std::unordered_map<std::string, std::shared_ptr<Shader>>
      m_Shaders;
  inline static std::unordered_map<UUID, std::shared_ptr<Texture>> m_Textures;
};
} // namespace Hamster
