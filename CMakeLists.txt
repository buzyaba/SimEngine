cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

if(WIN32)
    option(gtest_force_shared_crt "" TRUE)
endif(WIN32)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin" )


project(SimEngine)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/glew")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/bullet3")

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/glfw/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/glew/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/glm")
include_directories("${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/stb")
include_directories("${CMAKE_SOURCE_DIR}/lib/bullet3/src")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")


