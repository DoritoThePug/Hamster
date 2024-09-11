//
// Created by jaden on 07/09/24.
//

#include "Scripting.h"

#include <Core/Components.h>
#include <entt/entity/entity.hpp>
#include <fstream>
#include <pybind11/embed.h>
#include <pybind11/eval.h>
#include <pybind11/pybind11.h>

#include "Core/Project.h"
#include "Utils/AssetManager.h"

namespace Hamster {
  // std::filesystem::path Scripting::GenerateDefaultPythonScript(const
  // std::filesystem::path &path, std::string &entityName, UUID &entityUUID) {
  //     std::string fileName = entityName + entityUUID.GetUUIDString() + ".py";
  //
  //     std::ofstream out(path / fileName);
  //
  //     if (out.is_open()) {
  //         out << "import Hamster\n\n";
  //         out << "class" << entityName << ":\n";
  //         out << "def OnUpdate():\n";
  //         out << "pass\n";
  //
  //         out.close();
  //     }
  // }

  void Scripting::Init() {
    // pybind11::globals()["GetPosition"] = []() {
    //   std::cout << num << std::endl;
    // }

    if (!guard) {
      guard = std::make_unique<pybind11::scoped_interpreter>();
    }
  }

  void Scripting::Terminate() { pybind11::finalize_interpreter(); }

  void Scripting::AddScriptComponent(UUID &entityUUID,
                                     std::shared_ptr<Scene> scene) {
    Init();

    // std::string fileName = registry.get<ID>(entity).uuid.GetUUIDString();
    std::string fileName = entityUUID.GetUUIDString();

    std::filesystem::path scriptPath =
        Project::GetCurrentProject()->GetConfig().ProjectDirectory /
        (fileName + ".py");

    // Init();

    std::ofstream scriptOut(scriptPath);

    std::string defaultContent = "import Hamster \n\n"
        "class test(Hamster.HamsterBehaviour):\n"
        "    def OnUpdate(self):\n"
        "        print(' hi ')\n"
        "class hi(Hamster.HamsterBehaviour):\n"
        "    def OnUpdate(self):\n"
        "        pass\n";

    scriptOut << defaultContent;

    scriptOut.close();

    UUID uuidt = AssetManager::AddScript(scriptPath, fileName);

    if (!scene->EntityHasComponent<Behaviour>(entityUUID)) {
      scene->AddEntityComponent<Behaviour>(entityUUID);
    }

    scene->GetEntityComponent<Behaviour>(entityUUID).scripts.push_back(AssetManager::GetScript(uuidt));

    // Terminate();

    // pybind11::module_ script = pybind11::module_::import(fileName.c_str());

    // ReadScript(fileName);

    // pybind11::module_ scriptModule =
    // pybind11::module::import(fileName.c_str());

    // registry.emplace<Script>(entity, scriptModule, scriptPath);
    //

    // scripts.push_back(scriptPath);
    // behaviours.push_back(ReadScript(defaultContent));
  }

  void Scripting::ReadScript(std::string &fileName) {
    // pybind11::scoped_interpreter guard{};

    // Terminate();
  }
} // namespace Hamster
