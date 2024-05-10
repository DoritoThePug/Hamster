cmake_minimum_required(VERSION 3.29)

project(Hamster VERSION 1.0
                DESCRIPTION "An intuitive game engine made for python"
                LANGUAGES CXX
)

add_subdirectory(Hamster-Core)
add_subdirectory(Hamster-App)

add_subdirectory(Hamster-Core/Vendor/glfw)
add_subdirectory(Hamster-Core/Vendor/pybind11)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Hamster-App)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)