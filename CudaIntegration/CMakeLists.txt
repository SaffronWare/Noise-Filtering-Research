
cmake_minimum_required(VERSION 3.15)

project(CudaIntegration LANGUAGES CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CudaIntegration "Main.cu" "Render.cu" "Render.cuh" "Export.cpp" "Export.h" "debug.h" "Camera.cu" "Camera.cuh" "Ray.cuh" "Ray.cu")

target_link_libraries(CudaIntegration PUBLIC glm)