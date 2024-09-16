//
// Created by Jaden on 31/08/2024.
//

#include "HamsterPCH.h"

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
  //
  return projectConfig;
}
} // namespace Hamster
