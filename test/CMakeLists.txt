cmake_minimum_required(VERSION 3.28)
project(test)

find_package(Python COMPONENTS Interpreter Development REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(test main.cpp)

target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/Hamster-Py/Vendor/pybind11/include ${Python_INCLUDE_DIRS})


target_link_libraries(test PRIVATE pybind11::embed)




