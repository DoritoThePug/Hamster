cmake_minimum_required(VERSION 3.28)
project(Hamster-Core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(GLFW_INCLUDE_NONE)

# file(GLOB sources
#     src/Core/*.cpp src/Core/*.h
#     vendor/stb_image/stb_image.h vendor/stb_image/stb_image.cpp)
# file(GLOB SOURCES "src/*.h")
# file(GLOB SOURCES "vendor/stb_image/stb_image.h")
# file(GLOB SOURCES  "vendor/stb_image/stb_image.cpp")

file(GLOB source_core
        src/Core/*.cpp src/Core/*.h
)

source_group(Core FILES ${source_core})

file(GLOB source_events
        src/Events/*.cpp src/Events/*.h
)

source_group(Events FILES ${source_events})

file(GLOB source_renderer
        src/Renderer/*.cpp src/Renderer/*.h
)

source_group(Renderer FILES ${source_renderer})

file(GLOB source_utils
        src/Utils/*.cpp src/Utils/*.h
)

source_group(Utils FILES ${source_utils})

file(GLOB source_stb_image
        src/Core/stb_image.cpp src/stb/*.h
)

file(GLOB source_gui
        src/Gui/*.cpp src/Gui/*.h
)

source_group(Gui FILES ${source_gui})

set(sources
        ${source_core}
        ${source_events}
        ${source_renderer}
        ${source_utils}
        ${source_stb_image}
        ${source_gui}
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

target_link_libraries(Hamster-Core PUBLIC glfw)
target_link_libraries(Hamster-Core PUBLIC imgui)
# target_link_directories(Hamster-Core PUBLIC pybind11)

# Pybind 11 files
# pybind11_add_module(ass src/Core/pytest.cpp)
