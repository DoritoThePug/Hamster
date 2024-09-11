#include "HamsterScript.h"

#include "Core/Project.h"
//
namespace Hamster {
HamsterScript::HamsterScript(const std::filesystem::path &scriptPath,
                             const std::string &fileName)
    : m_ScriptPath(scriptPath) {
  pybind11::module sys = pybind11::module::import("sys");
  //
  pybind11::list path = sys.attr("path");
  path.append(
      Project::GetCurrentProject()->GetConfig().ProjectDirectory.string());
  //
  //   // if (!scene->EntityHasComponent<Behaviour>(entityUUID)) {
  //   // scene->AddEntityComponent<Behaviour>(entityUUID);
  //   // }
  //
  //   // Behaviour &behaviour =
  //   scene->GetEntityComponent<Behaviour>(entityUUID);
  //
  //   // behaviour.scripts.push_back(scriptPath);
  //
  pybind11::module_ script = pybind11::module_::import(fileName.c_str());
  //
  pybind11::object hamsterBehaviourClass =
      pybind11::module_::import("Hamster").attr("HamsterBehaviour");
  //
  for (auto &item : script.attr("__dict__").cast<pybind11::dict>()) {
    auto obj = item.second;
    //
    if (pybind11::hasattr(obj, "__bases__") &&
        pybind11::hasattr(hamsterBehaviourClass, "__name__")) {
      if (pybind11::bool_(
              pybind11::module_::import("builtins")
                  .attr("issubclass")(obj, hamsterBehaviourClass))) {
        m_PyObjects.push_back(obj);

        // behaviour.pyObjects.push_back(instance);

        // instance.attr("OnUpdate")();
      }
    }
  }
}
} // namespace Hamster
