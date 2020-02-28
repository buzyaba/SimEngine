cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 17)

set(SIMENGINE_PROJECT_NAME SimEngine)

project(${SIMENGINE_PROJECT_NAME})

if(WIN32)
    option(gtest_force_shared_crt "" TRUE)
endif(WIN32)

# Директории
set(SIMENGINE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} CACHE STRING "Output directory")
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${SIMENGINE_OUTPUT_DIRECTORY}/bin" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RELEASE" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DEBUG" )
set(SIMENGINE_OUTPUT_LEVEL "L0" CACHE STRING "Set level of output (L0, L1, L2)")

# Определяем компилятор
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(IS_GNU_COMPILER True)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(IS_INTEL_COMPILER True)	
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(IS_MICROSOFT_COMPILER True)
else()
    #message(FATAL_ERROR "Unsupported compiler")
	message("Unsupported compiler")
endif()

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)

if (NOT (CMAKE_BUILD_TYPE IN_LIST CMAKE_CONFIGURATION_TYPES))
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "build type" FORCE)
  message(STATUS "Unknown build type has been changed to " ${CMAKE_BUILD_TYPE})
endif()

#add graphic libraries
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/glew")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/bulletphys")

#add xml parser lib
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/pugixml)

#build output system
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/output_system)

#add tests
enable_testing()
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest")
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests)


#Создаем папки
if (IS_MICROSOFT_COMPILER)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set_property(TARGET pugixml PROPERTY FOLDER "3rd-party")
  set_property(TARGET gtest PROPERTY FOLDER "3rd-party")  
  
  set_property(TARGET Bullet2FileLoader PROPERTY FOLDER "3rd-party")
  set_property(TARGET Bullet3Collision PROPERTY FOLDER "3rd-party")
  set_property(TARGET Bullet3Common PROPERTY FOLDER "3rd-party")
  set_property(TARGET Bullet3Dynamics PROPERTY FOLDER "3rd-party") 
  set_property(TARGET Bullet3Geometry PROPERTY FOLDER "3rd-party")
  set_property(TARGET Bullet3OpenCL_clew PROPERTY FOLDER "3rd-party")
  set_property(TARGET BulletCollision PROPERTY FOLDER "3rd-party")
  set_property(TARGET BulletDynamics PROPERTY FOLDER "3rd-party")  
  set_property(TARGET BulletInverseDynamics PROPERTY FOLDER "3rd-party")
  set_property(TARGET BulletSoftBody PROPERTY FOLDER "3rd-party")
  set_property(TARGET gmock PROPERTY FOLDER "3rd-party")
  set_property(TARGET gmock_main PROPERTY FOLDER "3rd-party") 
  #set_property(TARGET libglew_shared PROPERTY FOLDER "3rd-party")
  #set_property(TARGET libglew_static PROPERTY FOLDER "3rd-party")
  #set_property(TARGET libglewmx_shared PROPERTY FOLDER "3rd-party")
  set_property(TARGET libglewmx_static PROPERTY FOLDER "3rd-party")  
  set_property(TARGET LinearMath PROPERTY FOLDER "3rd-party")  
  set_property(TARGET gtest_main PROPERTY FOLDER "3rd-party")  
endif()

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/glfw/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/glew/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/glm")
include_directories("${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/stb")
include_directories("${CMAKE_SOURCE_DIR}/lib/bulletphys/src")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")


