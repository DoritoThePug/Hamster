cmake_minimum_required(VERSION 3.28)
project(Hamster-App)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(Hamster-App ${SOURCES})

target_include_directories(Hamster-App PRIVATE
    src
    ${CMAKE_SOURCE_DIR}/Hamster-Core/src
    ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/glm
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/imgui
)

target_link_libraries(Hamster-App PRIVATE Hamster-Core)
target_link_libraries(Hamster-App PRIVATE glfw)
target_link_libraries(Hamster-App PRIVATE imgui)