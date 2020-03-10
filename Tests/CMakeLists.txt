cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME_STR tests)
project (${PROJECT_NAME_STR})

#add_executable(test mainTest.cpp)

#target_link_libraries(test gtest)

set(TESTS_OUTPUT_DIRECTORY ${SIMENGINE_OUTPUT_DIRECTORY})


file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME_STR} ${SRC_FILES})
set_target_properties(${PROJECT_NAME_STR} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_OUTPUT_DIRECTORY})
target_link_libraries(${PROJECT_NAME_STR}
						gtest
						pugixml
						output_system
						Core
						SmartHouseData
                        TrafficSimData
                        libglewmx_static
						BulletDynamics
						BulletCollision
						LinearMath 
						glfw ${OPENGL_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set_target_properties(${PROJECT_NAME_STR} PROPERTIES LINK_FLAGS "-lm -Wl,--no-as-needed -ldl -lpthread")
endif()

add_test(all_tests ${TESTS_OUTPUT_DIRECTORY}/${PROJECT_NAME_STR})
