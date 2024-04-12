IncludeDir = {}

IncludeDir["GLFW"] = "%{wks.location}/Hamster-Core/Vendor/GLFW/include"
IncludeDir["glad"] = "%{wks.location}/Hamster-Core/Vendor/glad/include"

LibraryDir = {}

LibraryDir["GLFW"] = "%{wks.location}/Hamster-Core/Vendor/GLFW"

Library = {}

Library["GLFW"] = "%{LibraryDir.GLFW}/glfw3.lib"