cmake_minimum_required(VERSION 3.28)
project(Hamster-Core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(GLFW_INCLUDE_NONE)

set(Core
        src/Core/Application.cpp
        src/Core/Application.h
        src/Core/Base.h
        src/Core/GameObject.cpp
        src/Core/GameObject.h
        src/Core/Layer.h
        src/Core/LayerStack.cpp
        src/Core/LayerStack.h
        src/Core/stb_image.cpp
        src/Core/Window.cpp
        src/Core/Window.h
)

set(Events
        src/Events/ApplicationEvents.h
        src/Events/Event.cpp
        src/Events/Event.h
        src/Events/GuiEvents.h
        src/Events/InputEvents.h
        src/Events/WindowEvents.h
)



set(Renderer
        src/Renderer/FramebufferTexture.cpp
        src/Renderer/FramebufferTexture.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/Renderer/Shader.cpp
        src/Renderer/Shader.h
        src/Renderer/Texture.cpp
        src/Renderer/Texture.h
)


set(Utils
        src/Utils/AssetManager.cpp
        src/Utils/AssetManager.h
        src/Utils/InputManager.cpp
        src/Utils/InputManager.h
)


set(Stb_Image
        src/Core/stb_image.cpp Vendor/stb/stb_image.h
)

set(Gui
        src/Gui/ImGuiLayer.cpp
        src/Gui/ImGuiLayer.h
        src/Gui/Panel.h
)

set(sources
        ${Core}
        ${Events}
        ${Renderer}
        ${Utils}
        ${Stb_Image}
        ${Gui}
        Vendor/glad/src/glad.c
)

add_library(Hamster-Core STATIC ${sources})

# find_package(Python COMPONENTS Interpreter Development REQUIRED)

target_include_directories(Hamster-Core PUBLIC
        src
        Vendor/glad/include
        Vendor/glm
        Vendor/stb
        Vendor/pybind11/include
        ${Python_INCLUDE_DIRS}
        Vendor/imgui
        Vendor/imgui/backends
        Vendor/entt/src
)

# message("-----------------------------------------${Python_INCLUDE_DIRS}")


target_include_directories(Hamster-Core PUBLIC Vendor/glfw/include)

# link_directories(
#     vendor/GLFW
#     vendor/glad/bin
# )


# add_subdirectory(${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/pybind11)

target_link_libraries(Hamster-Core PUBLIC glfw imgui)

# target_link_directories(Hamster-Core PUBLIC pybind11)

# Pybind 11 files
# pybind11_add_module(ass src/Core/pytest.cpp)

