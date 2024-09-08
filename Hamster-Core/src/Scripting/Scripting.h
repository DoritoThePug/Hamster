//
// Created by jaden on 07/09/24.
//

#ifndef SCRIPTING_H
#define SCRIPTING_H
#include <filesystem>
#include "Core/UUID.h"

#include <entt/entt.hpp>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace Hamster {
    class Scripting {
    public:
        // static std::filesystem::path GenerateDefaultPythonScript(const std::filesystem::path& path, std::string& entityName, UUID& entityUUID);

        static void Init();

        static void AddScriptComponent(entt::entity &entity, entt::registry &registry);

    private:
        inline static pybind11::scoped_interpreter m_Interpreter{};
    };
} // Hamster

#endif //SCRIPTING_H
