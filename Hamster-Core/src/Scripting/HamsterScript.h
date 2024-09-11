#pragma once

#include <filesystem>
#include <pybind11/pybind11.h>
//
// #include "Core/Project.h"
// #include "Core/Scene.h"
#include <iostream>

#include "Core/UUID.h"
//
namespace Hamster {
class Scene;
struct ID;
//     // class HamsterBehaviour;
class UUID;
class HamsterScript {
public:
  HamsterScript(const std::filesystem::path &scriptPath,
                const std::string &fileName);

  //
  [[nodiscard]] std::filesystem::path GetScriptPath() { return m_ScriptPath; std::cout << m_ScriptPath << std::endl;}
  //
  void SetUUID(UUID uuid) { m_UUID = uuid; }
  UUID GetUUID() { return m_UUID; }
  //
  void SetName(const std::string &name) { m_ScriptName = name; }
  const std::string &GetName() { return m_ScriptName; }
  //
  std::vector<pybind11::handle> const &GetPyObjects() { return m_PyObjects; }
  //
private:
  const std::string m_ScriptPath;
  std::string m_ScriptName = "Untitled Scripts";
  UUID m_UUID;
  std::vector<pybind11::handle> m_PyObjects;
};
} // namespace Hamster
