cmake_minimum_required(VERSION 3.28)
project(Hamster-Py)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Python COMPONENTS Interpreter Development REQUIRED)



file(GLOB source
    src/*.cpp
    src/*.h
)



add_library(Hamster-Py STATIC ${source})


target_include_directories(Hamster-Py PUBLIC
    src
    ${CMAKE_SOURCE_DIR}/Hamster-Core/src
    ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/glm
    Vendor/pybind11/include
    ${Python_INCLUDE_DIRS}
)

add_subdirectory(Vendor/pybind11)


target_link_libraries(Hamster-Py PUBLIC Hamster-Core)
target_link_libraries(Hamster-Py PUBLIC glfw)

pybind11_add_module(Hamster src/main.cpp)

target_include_directories(Hamster PUBLIC
    src
    ${CMAKE_SOURCE_DIR}/Hamster-Core/src
    ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/glm
    Vendor/pybind11/include
    ${Python_INCLUDE_DIRS}
)

target_link_libraries(Hamster PUBLIC Hamster-Core)
target_link_libraries(Hamster PUBLIC glfw)




# target_link_directories(Hamster-Py PUBLIC pybind11)

