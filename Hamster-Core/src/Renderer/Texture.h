#pragma once

#include <ostream>

#include <glad/glad.h>

#include "Core/UUID.h"

namespace Hamster {
struct TextureData {
  unsigned char *data;
  int width, height, nrChannels;
};

class Texture {
public:
  Texture(const std::string &texturePath);
  Texture() {};

  void Init(const TextureData &textData);

  void BindTexture();

  [[nodiscard]] const std::string &GetTexturePath() const {
    return m_TexturePath;
  }

  void SetUUID(const UUID &uuid) { m_UUID = uuid; };
  UUID GetUUID() { return m_UUID; };

  void SetName(const std::string &name) { m_TextureName = name; }
  const std::string &GetName() { return m_TextureName; }

  GLuint GetTextureId() { return m_ID; }

private:
  GLuint m_ID;
  const std::string m_TexturePath;
  std::string m_TextureName = "Untitled Texture";
  UUID m_UUID;
};
} // namespace Hamster
