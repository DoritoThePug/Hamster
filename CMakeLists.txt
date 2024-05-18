cmake_minimum_required(VERSION 3.29)

project(Hamster VERSION 1.0
                DESCRIPTION "An intuitive game engine made for python"
                LANGUAGES CXX
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Hamster-Core)
add_subdirectory(Hamster-App)
add_subdirectory(Hamster-Py)

add_subdirectory(Hamster-Core/Vendor/glfw)
