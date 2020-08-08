cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 14)

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

option(BUILD_TESTS "Set ON to build tests" ON)
option(BUILD_PLOTTER "Set ON to build plotter" OFF)
option(USE_OpenGL "Set ON to use OpenGL" ON)
option(BUILD_DLL "Set ON to build Dll" OFF)

# Определяем компилятор
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(IS_GNU_COMPILER True)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(IS_INTEL_COMPILER True)	
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(IS_MICROSOFT_COMPILER True)
else()
	message("Unsupported compiler")
endif()

if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	set(SIMENGINE_TARGET_ARCH "x64")
elseif (${CMAKE_SIZEOF_VOID_P} EQUAL 4)
	set(SIMENGINE_TARGET_ARCH "x86")
else()
	set(SIMENGINE_TARGET_ARCH "x86")
	message("Unsupported architecture")
endif()

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)

if (NOT (CMAKE_BUILD_TYPE IN_LIST CMAKE_CONFIGURATION_TYPES))
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "build type" FORCE)
  message(STATUS "Unknown build type has been changed to " ${CMAKE_BUILD_TYPE})
endif()

  #set(dislin_includedir ${PROJECT_SOURCE_DIR}/lib/dislin/include)
  #if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  #  set(dislin_libpath ${PROJECT_SOURCE_DIR}/lib/dislin/lib/lnx/libdiscpp.so.10
  #     ${PROJECT_SOURCE_DIR}/lib/dislin/lib/lnx/discpp-10.6.so)
  #elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  #  if (SIMENGINE_TARGET_ARCH MATCHES "x86")
  #    set(dislin_libpath ${PROJECT_SOURCE_DIR}/lib/dislin/lib/win/x86/discpp.lib)
  #  elseif (SIMENGINE_TARGET_ARCH MATCHES "x64")
  #    set(dislin_libpath ${PROJECT_SOURCE_DIR}/lib/dislin/lib/win/x64/discpp.lib)
  #  endif()
  #endif()
  #
  #message(WARNING "dislin = ${CMAKE_SIZEOF_VOID_P}")

#add graphic libraries
if (${USE_OpenGL})
	option (glew-cmake_BUILD_SHARED "Build shared libraries" ON)
	set(glew-cmake_BUILD_SHARED OFF)
	option(glew-cmake_BUILD_SINGLE_CONTEXT "Build the single context glew library" ON)
	set(glew-cmake_BUILD_SINGLE_CONTEXT OFF)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw")
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/glew")
	OPTION( BUILD_SHARED_LIBS
	"Build package with shared libraries."
	ON
	)
	set(BUILD_SHARED_LIBS OFF)
	OPTION( ASSIMP_BUILD_ASSIMP_TOOLS
	"If the supplementary tools for Assimp are built in addition to the library."
	ON
	)
	set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
	OPTION ( ASSIMP_BUILD_TESTS
	"If the test suite for Assimp is built in addition to the library."
	ON
	)
	set(ASSIMP_BUILD_TESTS OFF)
	OPTION( ASSIMP_INSTALL
	"Disable this if you want to use assimp as a submodule."
	ON
	)
	set(ASSIMP_INSTALL OFF) 
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp")
	add_definitions(-DUSE_OPENGL)
endif()

if (${BUILD_PLOTTER})
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/matplotlib-cpp")
endif()

#add xml parser lib
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/pugixml)

#build output system
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/output_system)

# Поиск пакетов

if (${BUILD_PLOTTER})
	find_package(Python3 COMPONENTS Development)
	add_definitions(-DUSE_PLOTTER)
	include_directories(${Python3_INCLUDE_DIRS})	
	include_directories("${CMAKE_SOURCE_DIR}/lib/matplotlib-cpp")
endif()

if (${USE_OpenGL})
	include_directories(${OPENGL_INCLUDE_DIRS})
	find_package(OpenGL REQUIRED)
	include_directories("${CMAKE_SOURCE_DIR}/lib/glfw/include")
	include_directories("${CMAKE_SOURCE_DIR}/lib/glew/include")
	include_directories("${CMAKE_SOURCE_DIR}/lib/glm")
	include_directories("${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include")
	include_directories("${CMAKE_SOURCE_DIR}/lib/stb")
	include_directories("${CMAKE_SOURCE_DIR}/lib/assimp/include")
endif()

include_directories("${CMAKE_SOURCE_DIR}/lib")
include_directories("${CMAKE_SOURCE_DIR}/include")


#add tests
if (${BUILD_TESTS})
	enable_testing()
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest")
	add_subdirectory(${PROJECT_SOURCE_DIR}/Tests)
endif()

if (${BUILD_DLL})
	add_definitions(-DUSE_DLL_OBJ)
endif()	

#подключение основного кода, ВСЕ КОНСТАНТЫ И ПЕРЕМЕННЫЕ ДОЛЖНЫ БЫТЬ ОПРЕДЕЛЕНЫ ДО ЭТОГО
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Создавать ли dll c дополнительными объектами
if (${BUILD_DLL})
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Dll")
endif()

#Создаем папки
if (IS_MICROSOFT_COMPILER)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set_property(TARGET pugixml PROPERTY FOLDER "3rd-party")
	
	if (${BUILD_TESTS})
		set_property(TARGET gtest PROPERTY FOLDER "3rd-party")  
		set_property(TARGET gtest_main PROPERTY FOLDER "3rd-party")  
		set_property(TARGET gmock PROPERTY FOLDER "3rd-party")
		set_property(TARGET gmock_main PROPERTY FOLDER "3rd-party") 
	endif()
	
	if (${USE_OpenGL})
		#set_property(TARGET libglew_shared PROPERTY FOLDER "3rd-party")
		#set_property(TARGET libglew_static PROPERTY FOLDER "3rd-party")
		#set_property(TARGET libglewmx_shared PROPERTY FOLDER "3rd-party")
		set_property(TARGET libglewmx_static PROPERTY FOLDER "3rd-party")  
		# set_property(TARGET LinearMath PROPERTY FOLDER "3rd-party")  
	endif()

	if (${BUILD_PLOTTER})
		set_property(TARGET MatplotlibC++ PROPERTY FOLDER "3rd-party")  
	endif()
endif()

