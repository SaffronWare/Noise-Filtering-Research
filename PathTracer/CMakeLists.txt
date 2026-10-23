# CMakeList.txt : CMake project for Noise-Filtering-Path-Tracing, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (PathTracer "Main.cpp"  "Ray.h" "Ray.cpp" "Camera.h" "Camera.cpp" "Objects.h" "Objects.cpp" "Scene.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PathTracer PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(PathTracer PRIVATE glm)

# TODO: Add tests and install targets if needed.
