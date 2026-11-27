
cmake_minimum_required(VERSION 3.15)

project(CudaIntegration LANGUAGES CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CudaIntegration "Main.cu" "Render.cu" "Render.cuh" "Export.cpp" "Export.h" "config.h" "Camera.cu" "Camera.cuh" "Ray.cuh" "Ray.cu")

set_property(TARGET CudaIntegration PROPERTY CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(CudaIntegration PUBLIC glm)