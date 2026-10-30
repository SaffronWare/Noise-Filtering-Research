# CMakeList.txt : CMake project for Noise-Filtering-Path-Tracing, include source and define
# project specific logic here.
#

find_package(OpenMP REQUIRED)

# Add source to this project's executable.
add_executable (PathTracer "Main.cpp"  "Ray.h" "Ray.cpp" "Camera.h" "Camera.cpp" "Objects.h" "Objects.cpp" "Scene.h" "Renderer.h" "Renderer.cpp" "Export.h" "Export.cpp"   "utils.h" "utils.cpp" "DisneyBrdf.h" "DisneyBrdf.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PathTracer PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(PathTracer PRIVATE glm)
target_link_libraries(PathTracer PRIVATE OpenMP::OpenMP_CXX)

# TODO: Add tests and install targets if needed.
