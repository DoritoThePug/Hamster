CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
project(imgui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(sources
        imconfig.h
        imgui.cpp
        imgui.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_internal.h
        imgui_tables.cpp
        imgui_widgets.cpp
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        misc/cpp/imgui_stdlib.cpp
        misc/cpp/imgui_stdlib.h
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_glfw.h
        backends/imgui_impl_opengl3.cpp
        backends/imgui_impl_opengl3.h
)

add_library(imgui STATIC ${sources})

target_include_directories(imgui PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Hamster-Core/Vendor/glfw/include
)

target_link_directories(imgui PRIVATE glfw)