cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME_STR output_system)
project (${PROJECT_NAME_STR})

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(${PROJECT_NAME_STR} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME_STR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME_STR} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${SIMENGINE_OUTPUT_DIRECTORY})

if(${SIMENGINE_OUTPUT_LEVEL} MATCHES "L1")
  target_compile_definitions(${PROJECT_NAME_STR} PUBLIC -DSIMENGINE_OUTPUT_L1)
elseif(${SIMENGINE_OUTPUT_LEVEL} MATCHES "L2")
  target_compile_definitions(${PROJECT_NAME_STR} PUBLIC -DSIMENGINE_OUTPUT_L2)
endif()

if(CMAKE_BUILD_TYPE MATCHES "DEBUG|Debug")
  target_compile_definitions(${PROJECT_NAME_STR} PUBLIC -D_DEBUG)
endif()

if (IS_MICROSOFT_COMPILER)
  set_property(TARGET ${PROJECT_NAME_STR} PROPERTY FOLDER "3rd-party")
endif()
