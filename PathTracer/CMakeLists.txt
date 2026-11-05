
cmake_minimum_required(VERSION 3.15)

project(PathTracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PYBIND11_FINDPYTHON ON)

find_package(OpenMP REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# Shared rendering engine
add_library(PathTracerCore STATIC
    Ray.cpp
    Camera.cpp
    Objects.cpp
    Renderer.cpp
    Export.cpp
    utils.cpp
    DisneyBrdf.cpp
    Analysis.cpp
 "Setup.h" "Setup.cpp")

target_include_directories(PathTracerCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(PathTracerCore PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(PathTracerCore PUBLIC
    glm
    OpenMP::OpenMP_CXX
)

# Standalone C++ application
add_executable(PathTracer Main.cpp "Setup.h" "Setup.cpp")

target_link_libraries(PathTracer PRIVATE PathTracerCore)

# Python bindings
pybind11_add_module(PathTracerPy PyInterface.cpp)

target_link_libraries(PathTracerPy PRIVATE PathTracerCore)

set_target_properties(PathTracerPy PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}\\Analysis"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}\\Analysis"
)