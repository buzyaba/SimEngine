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
option(USE_OPENGL "Set ON to use OpenGL" ON)

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

if (UNIX)
	set(CMAKE_CXX_FLAGS "-fPIC")
	set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
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
if (${USE_OPENGL})
	option(glew-cmake_BUILD_STATIC "Build the static glew library" ON)
	set(glew-cmake_BUILD_STATIC OFF)
	option(glew-cmake_BUILD_MULTI_CONTEXT "Build the multi context glew library" ON)
	set(glew-cmake_BUILD_MULTI_CONTEXT OFF)
	option(ONLY_LIBS "Do not build executables" OFF)
	set(ONLY_LIBS ON)
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
	set(ASSIMP_BUILD_X_IMPORTER OFF)
	set(ASSIMP_BUILD_AMF_IMPORTER OFF)
	set(ASSIMP_BUILD_3DS_IMPORTER OFF)
	set(ASSIMP_BUILD_MD3_IMPORTER OFF)
	set(ASSIMP_BUILD_MDL_IMPORTER OFF)
	set(ASSIMP_BUILD_MD2_IMPORTER OFF)
	set(ASSIMP_BUILD_PLY_IMPORTER OFF)
	set(ASSIMP_BUILD_ASE_IMPORTER OFF)
	set(ASSIMP_BUILD_HMP_IMPORTER OFF)
	set(ASSIMP_BUILD_SMD_IMPORTER OFF)
	set(ASSIMP_BUILD_MDC_IMPORTER OFF)
	set(ASSIMP_BUILD_MD5_IMPORTER OFF)
	set(ASSIMP_BUILD_STL_IMPORTER OFF)
	set(ASSIMP_BUILD_LWO_IMPORTER OFF)
	set(ASSIMP_BUILD_DXF_IMPORTER OFF)
	set(ASSIMP_BUILD_NFF_IMPORTER OFF)
	set(ASSIMP_BUILD_RAW_IMPORTER OFF)
	set(ASSIMP_BUILD_SIB_IMPORTER OFF)
	set(ASSIMP_BUILD_OFF_IMPORTER OFF)
	set(ASSIMP_BUILD_AC_IMPORTER OFF)
	set(ASSIMP_BUILD_BVH_IMPORTER OFF)
	set(ASSIMP_BUILD_IRRMESH_IMPORTER OFF)
	set(ASSIMP_BUILD_IRR_IMPORTER OFF)
	set(ASSIMP_BUILD_Q3D_IMPORTER OFF)
	set(ASSIMP_BUILD_B3D_IMPORTER OFF)
	set(ASSIMP_BUILD_COLLADA_IMPORTER OFF)
	set(ASSIMP_BUILD_TERRAGEN_IMPORTER OFF)
	set(ASSIMP_BUILD_CSM_IMPORTER OFF)
	set(ASSIMP_BUILD_3D_IMPORTER OFF)
	set(ASSIMP_BUILD_LWS_IMPORTER OFF)
	set(ASSIMP_BUILD_OGRE_IMPORTER OFF)
	set(ASSIMP_BUILD_OPENGEX_IMPORTER OFF)
	set(ASSIMP_BUILD_MS3D_IMPORTER OFF)
	set(ASSIMP_BUILD_COB_IMPORTER OFF)
	set(ASSIMP_BUILD_BLEND_IMPORTER OFF)
	set(ASSIMP_BUILD_Q3BSP_IMPORTER OFF)
	set(ASSIMP_BUILD_NDO_IMPORTER OFF)
	set(ASSIMP_BUILD_IFC_IMPORTER OFF)
	set(ASSIMP_BUILD_XGL_IMPORTER OFF)
	set(ASSIMP_BUILD_FBX_IMPORTER OFF)
	set(ASSIMP_BUILD_ASSBIN_IMPORTER OFF)
	set(ASSIMP_BUILD_GLTF_IMPORTER OFF)
	set(ASSIMP_BUILD_GLTF_IMPORTER OFF)
	set(ASSIMP_BUILD_C4D_IMPORTER OFF)
	set(ASSIMP_BUILD_3MF_IMPORTER OFF)
	set(ASSIMP_BUILD_X3D_IMPORTER OFF)
	set(ASSIMP_BUILD_MMD_IMPORTER OFF)
	set(ASSIMP_BUILD_M3D_IMPORTER OFF)
	OPTION( ASSIMP_NO_EXPORT
  "Disable Assimp's export functionality."
  OFF
)
	set(ASSIMP_NO_EXPORT ON)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp")
	add_definitions(-DUSE_OPENGL)
endif()

#add xml parser lib
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/pugixml)

#build output system
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/output_system)

# Поиск пакетов
if (${USE_OPENGL})
	include_directories(${OPENGL_INCLUDE_DIRS})
	find_package(OpenGL REQUIRED)
	include_directories("${CMAKE_SOURCE_DIR}/lib/glfw/include")
	include_directories("${CMAKE_SOURCE_DIR}/lib/glew/include")
	include_directories("${CMAKE_SOURCE_DIR}/lib/glm")
	include_directories("${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include")
	include_directories("${CMAKE_SOURCE_DIR}/lib/stb")
	include_directories("${CMAKE_SOURCE_DIR}/lib/assimp/include")
	include_directories("${CMAKE_SOURCE_DIR}/lib/assimp/contrib")
	include_directories("${CMAKE_BINARY_DIR}/lib/assimp/include")
endif()

include_directories("${CMAKE_SOURCE_DIR}/lib")
include_directories("${CMAKE_SOURCE_DIR}/include")


#add tests
if (${BUILD_TESTS})
	enable_testing()
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest")
	add_subdirectory(${PROJECT_SOURCE_DIR}/Tests)
endif()


#подключение основного кода, ВСЕ КОНСТАНТЫ И ПЕРЕМЕННЫЕ ДОЛЖНЫ БЫТЬ ОПРЕДЕЛЕНЫ ДО ЭТОГО
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Dll")

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
	
	if (${USE_OPENGL})
		set_property(TARGET libglew_shared PROPERTY FOLDER "3rd-party")
		#set_property(TARGET libglew_static PROPERTY FOLDER "3rd-party")
		#set_property(TARGET libglewmx_shared PROPERTY FOLDER "3rd-party")
		# set_property(TARGET libglew_shared PROPERTY FOLDER "3rd-party")  
		# set_property(TARGET LinearMath PROPERTY FOLDER "3rd-party")  
	endif()
endif()

