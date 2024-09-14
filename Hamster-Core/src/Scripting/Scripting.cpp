//
// Created by jaden on 07/09/24.
//

#include "Scripting.h"

#include "Core/Components.h"
#include <entt/entity/entity.hpp>
#include <fstream>
#include <pybind11/embed.h>
#include <pybind11/eval.h>
#include <pybind11/pybind11.h>

#include "Core/Project.h"
#include "Scripting/HamsterScript.h"
#include "Utils/AssetManager.h"

namespace Hamster {
std::filesystem::path Scripting::GenerateDefaultScript(UUID *uuidVal) {
  UUID scriptUUID;

  std::string fileName = "Untitled_Script_" + scriptUUID.GetUUIDString();

  std::filesystem::path scriptPath =
      Project::GetCurrentProject()->GetConfig().ProjectDirectory /
      (fileName + ".py");

  // Init();

  std::ofstream scriptOut(scriptPath);

  std::string defaultContent = "import Hamster \n\n"
                               "class test(Hamster.HamsterBehaviour):\n"
                               "    def OnUpdate(self):\n"
                               "        self.transform.position.x += 1\n"
                               "class hi(Hamster.HamsterBehaviour):\n"
                               "    def OnUpdate(self):\n"
                               "        pass";

  scriptOut << defaultContent;

  scriptOut.close();

  if (uuidVal != nullptr) {
    *uuidVal = scriptUUID;
  }

  return scriptPath;
}

} // namespace Hamster
