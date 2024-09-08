cmake_minimum_required(VERSION 3.28)
project(Hamster-Wheel)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Python COMPONENTS Interpreter Development REQUIRED)

add_compile_definitions(GLFW_EXPOSE_NATIVE_WIN32)
add_compile_definitions(GLFW_INCLUDE_NONE)

set(PANELS
        src/Panels/PropertyEditor.cpp src/Panels/PropertyEditor.h


        src/Panels/Hierarchy.cpp src/Panels/Hierarchy.h


        src/Panels/StartPauseModal.cpp src/Panels/StartPauseModal.h

        src/Panels/MenuBar.cpp src/Panels/MenuBar.h
        src/Panels/ProjectCreator.cpp
        src/Panels/ProjectCreator.h
        src/Panels/ProjectSelector.cpp
        src/Panels/ProjectSelector.h
        src/ProjectHubLayer.cpp
        src/Panels/FileBrowser.cpp
        src/Panels/FileBrowser.h
        src/Panels/AssetBrowser.cpp
        src/Panels/AssetBrowser.h

)

add_executable(Hamster-Wheel ${PANELS} src/EditorLayer.cpp src/EditorLayer.h src/HamsterWheelApp.cpp)

target_include_directories(Hamster-Wheel PRIVATE
        src
        ${CMAKE_SOURCE_DIR}/Hamster-Core/src
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/GLFW/include
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/glm
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/imgui
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/box2d/include
        Vendor/tinyfiledialogs
        Vendor/pybind11/include
        #        ${CMAKE_SOURCE_DIR}/Hamster-Py/Vendor/pybind11/include
        ${Python_INCLUDE_DIRS}
)

#add_subdirectory(Vendor/pybind11)
target_compile_definitions(Hamster-Wheel PRIVATE HAMSTER_WHEEL_SRC_DIR="${CMAKE_SOURCE_DIR}/Hamster-Wheel/src")

target_link_libraries(Hamster-Wheel PRIVATE Hamster-Core glfw imgui box2d tinyfiledialogs pybind11::embed)




