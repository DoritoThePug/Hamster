#include "HamsterScript.h"

#include "Core/Project.h"
#include "Scripting.h"

//
namespace Hamster {
  HamsterScript::HamsterScript(const std::filesystem::path &scriptPath,
                               const std::string &fileName)
    : m_ScriptPath(scriptPath.string()), m_FileName(fileName) {
    m_Module = pybind11::module_::import(m_FileName.c_str());
  }

  void HamsterScript::ReloadScript() {
    m_PyObjects.clear();

    m_Module.reload();
    //
    pybind11::object hamsterBehaviourClass =
        pybind11::module_::import("HamsterPCK.Hamster").attr("HamsterBehaviour");
    //
    for (auto &item: m_Module.attr("__dict__").cast<pybind11::dict>()) {
      auto obj = item.second;
      //
      if (pybind11::hasattr(obj, "__bases__") &&
          pybind11::hasattr(hamsterBehaviourClass, "__name__")) {
        if (pybind11::bool_(
          pybind11::module_::import("builtins")
          .attr("issubclass")(obj, hamsterBehaviourClass))) {
          m_PyObjects.push_back(obj);

          // behaviour.pyObjects.push_back(instance);

          // obj.attr("t")();
        }
      }
    }

    std::cout << m_PyObjects.size() << std::endl;
  }
} // namespace Hamster
