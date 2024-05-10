cmake_minimum_required(VERSION 3.29)
project(Hamster-Core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
    Vendor/stb_image/*.cpp src/stb_image/*.h
)

set(sources
    ${source_core}
    ${source_events}
    ${source_renderer}
    ${source_utils}
    ${source_stb_image}
    Vendor/glad/src/glad.c
)

add_library(Hamster-Core STATIC ${sources})

target_include_directories(Hamster-Core PRIVATE
    src
    vendor/glad/include
    vendor/glm
    vendor/stb_image
)

target_include_directories(Hamster-Core PUBLIC Vendor/glfw/include)

# link_directories(
#     vendor/GLFW
#     vendor/glad/bin
# )

target_link_directories(Hamster-Core PUBLIC glfw)