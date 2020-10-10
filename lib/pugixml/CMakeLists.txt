cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME_STR pugixml)
project (${PROJECT_NAME_STR})

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

add_library(${PROJECT_NAME_STR} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME_STR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(IS_GNU_COMPILER)
  target_compile_options(${PROJECT_NAME_STR} PUBLIC -fPIC)
endif()

if (IS_MICROSOFT_COMPILER)
  set_property(TARGET ${PROJECT_NAME_STR} PROPERTY FOLDER "3rd-party")
endif()
