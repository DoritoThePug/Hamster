IncludeDir = {}

IncludeDir["GLFW"] = "%{wks.location}/Hamster-Core/Vendor/GLFW/include"
IncludeDir["glad"] = "%{wks.location}/Hamster-Core/Vendor/glad/include"
IncludeDir["stb_image"] = "%{wks.location}/Hamster-Core/Vendor/stb_image"
IncludeDir["glm"] = "%{wks.location}/Hamster-Core/Vendor/glm"
IncludeDir["py"] = "%{wks.location}/Hamster-Core/Vendor/pybind11"

LibraryDir = {}

LibraryDir["GLFW"] = "%{wks.location}/Hamster-Core/Vendor/GLFW"

Library = {}

Library["GLFW"] = "%{LibraryDir.GLFW}/glfw3.lib"