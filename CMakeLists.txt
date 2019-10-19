cmake_minimum_required(VERSION 3.1)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )

project(SimEngine)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glew)
add_subdirectory(lib/googletest)


include_directories(include)
include_directories(lib/glfw/include)
include_directories(lib/glew/include)
include_directories(lib/glm)
include_directories(lib/googletest/googletest/include)

add_subdirectory(src)


