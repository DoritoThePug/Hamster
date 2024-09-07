//
// Created by Jaden on 31/08/2024.
//

#include "ProjectSerialiser.h"

#include "Utils/AssetManager.h"

namespace Hamster {
void ProjectSerialiser::Serialise(std::ostream &out) {
  const ProjectConfig &projectConfig = m_Project->GetConfig();

  std::size_t nameLength = projectConfig.Name.size();
  out.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
  out.write(projectConfig.Name.data(), nameLength);

  std::string projectPathStr = projectConfig.ProjectDirectory.string();

  std::size_t projectPathLength = projectPathStr.size();
  out.write(reinterpret_cast<const char *>(&projectPathLength),
            sizeof(projectPathLength));
  out.write(projectPathStr.data(), projectPathLength);

  std::string startScenePathStr = projectConfig.StartScenePath.string();

  std::size_t startScenePathLength = startScenePathStr.size();
  out.write(reinterpret_cast<const char *>(&startScenePathLength),
            sizeof(startScenePathLength));
  out.write(startScenePathStr.data(), startScenePathLength);

  uint32_t textureCount = AssetManager::GetTextureCount();

  out.write(reinterpret_cast<const char *>(&textureCount),
            sizeof(textureCount));

  // serialise texture asset manager
  for (auto const &[uuid, texture] : AssetManager::GetTextureMap()) {
    std::cout << "Serialising texture with uuid: " << uuid.GetUUID()
              << std::endl;

    UUID::Serialise(out, uuid);

    std::string texturePathStr = texture->GetTexturePath();

    std::size_t texturePathLength = texturePathStr.size();
    out.write(reinterpret_cast<const char *>(&texturePathLength),
              sizeof(texturePathLength));
    out.write(texturePathStr.data(), texturePathLength);

    std::string textureNameStr = texture->GetName();
    std::size_t textureNameLength = textureNameStr.size();
    out.write(reinterpret_cast<const char *>(&textureNameLength),
              sizeof(textureNameLength));
    out.write(textureNameStr.data(), textureNameLength);
  }
}

ProjectConfig ProjectSerialiser::Deserialise(std::istream &in) {
  ProjectConfig projectConfig;

  std::size_t nameLength;
  in.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));

  std::string nameStr(nameLength, '\0');
  in.read(nameStr.data(), nameLength);

  projectConfig.Name = nameStr;

  std::size_t projectPathLength;
  in.read(reinterpret_cast<char *>(&projectPathLength),
          sizeof(projectPathLength));

  std::string projectPathStr(projectPathLength, '\0');
  in.read(projectPathStr.data(), projectPathLength);

  projectConfig.ProjectDirectory = projectPathStr;

  std::size_t startScenePathLength;
  in.read(reinterpret_cast<char *>(&startScenePathLength),
          sizeof(startScenePathLength));

  std::string startScenePathStr(startScenePathLength, '\0');
  in.read(startScenePathStr.data(), startScenePathLength);

  projectConfig.StartScenePath = startScenePathStr;

  uint32_t textureCount;
  in.read(reinterpret_cast<char *>(&textureCount), sizeof(textureCount));

  for (uint32_t i = 0; i < textureCount; i++) {
    UUID uuid = UUID::Deserialise(in);

    std::size_t texturePathLength;
    in.read(reinterpret_cast<char *>(&texturePathLength),
            sizeof(texturePathLength));

    std::string texturePathStr(texturePathLength, '\0');
    in.read(texturePathStr.data(), texturePathLength);

    std::size_t textureNameLength;
    in.read(reinterpret_cast<char *>(&textureNameLength),
            sizeof(textureNameLength));

    std::string textureNameStr(textureNameLength, '\0');
    in.read(textureNameStr.data(), textureNameLength);

    AssetManager::AddTexture(uuid, texturePathStr, textureNameStr);
  }

  return projectConfig;
}
} // namespace Hamster
