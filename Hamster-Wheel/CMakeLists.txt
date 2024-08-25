cmake_minimum_required(VERSION 3.28)
project(Hamster-Wheel)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_compile_definitions(GLFW_INCLUDE_NONE)

set(PANELS
        src/Panels/PropertyEditor.cpp
        src/Panels/PropertyEditor.h

        src/Panels/Hierarchy.cpp
        src/Panels/Hierarchy.h
)

add_executable(Hamster-Wheel ${PANELS} src/EditorLayer.cpp src/EditorLayer.h src/HamsterWheelApp.cpp)

target_include_directories(Hamster-Wheel PRIVATE
        src
        ${CMAKE_SOURCE_DIR}/Hamster-Core/src
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/GLFW/include
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/glm
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/imgui
)

target_link_libraries(Hamster-Wheel PRIVATE Hamster-Core glfw imgui)



