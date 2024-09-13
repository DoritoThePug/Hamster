//
// Created by jaden on 07/09/24.
//

#ifndef SCRIPTING_H
#define SCRIPTING_H
#include "Core/UUID.h"
#include <entt/entt.hpp>
#include <filesystem>
#include <memory>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "HamsterBehaviour.h"

namespace Hamster {
class AssetManager;

class Scripting {
public:
  static void AddScriptComponent(UUID &uuid, std::shared_ptr<Scene> scene);

  static std::filesystem::path GenerateDefaultScript(UUID *uuid);

  static void InitInterpreter() {
    if (!m_InterpreterInitialised) {
      pybind11::initialize_interpreter();

      m_InterpreterInitialised = true;
    }
  }

  static void FinaliseInterpreter() {
    if (m_InterpreterInitialised) {
      pybind11::finalize_interpreter();

      m_InterpreterInitialised = false;
    }
  }

private:
  inline static bool m_InterpreterInitialised = false;
};
} // namespace Hamster

#endif // SCRIPTING_H
