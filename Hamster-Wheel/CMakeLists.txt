cmake_minimum_required(VERSION 3.28)
project(Hamster-Wheel)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(Hamster-Wheel ${SOURCES})

target_include_directories(Hamster-Wheel PRIVATE
        src
        ${CMAKE_SOURCE_DIR}/Hamster-Core/src
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/GLFW/include
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/glm
)

target_link_libraries(Hamster-Wheel PRIVATE Hamster-Core)
target_link_libraries(Hamster-Wheel` PRIVATE glfw)