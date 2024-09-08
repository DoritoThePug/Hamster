//
// Created by jaden on 07/09/24.
//

#include "Scripting.h"

#include <fstream>
#include <Core/Components.h>
#include <entt/entity/entity.hpp>
#include <pybind11/embed.h>
#include <pybind11/eval.h>

#include "Core/Project.h"

namespace Hamster {
    // std::filesystem::path Scripting::GenerateDefaultPythonScript(const std::filesystem::path &path, std::string &entityName, UUID &entityUUID) {
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
    }

    void Scripting::AddScriptComponent(entt::entity &entity, entt::registry &registry) {
        std::string fileName = registry.get<
            ID>(entity).uuid.GetUUIDString();

        std::filesystem::path scriptPath = Project::GetCurrentProject()->GetConfig().ProjectDirectory / (
                                               fileName + ".py");

        pybind11::module sys = pybind11::module::import("sys");
        sys.attr("path").attr("append")(scriptPath.string());


        std::ofstream scriptOut(scriptPath);

        std::string defaultContent = "#import Hamster \n\n"
                "def OnUpdate():\n"
                "    print('HI')\n";

        scriptOut << defaultContent;

        scriptOut.close();


        pybind11::module_ scriptModule = pybind11::module::import(fileName.c_str());

        registry.emplace<Script>(entity, scriptModule, scriptPath);
    }
} // Hamster
