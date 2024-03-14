-- premake5.lua
include "Dependencies.lua"

workspace "Hamster"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Hamster-App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Hamster-Core"
	include "Hamster-Core/Build-Core.lua"
group ""

include "Hamster-App/Build-App.lua"