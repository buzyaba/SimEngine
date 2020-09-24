file(GLOB_RECURSE source_files "*.cpp")

file(GLOB TRAFFIC_SIM ${CMAKE_SOURCE_DIR}/src/BasicExamples/TrafficSim/*.cpp)
list(REMOVE_ITEM TRAFFIC_SIM ${CMAKE_SOURCE_DIR}/src/BasicExamples/TrafficSim/main.cpp)

add_executable(SimEngine ${source_files} ${TRAFFIC_SIM})

add_definitions(-DGLEW_NO_GLU)

target_link_libraries(SimEngine						
						Core
						pugixml 
						output_system
						)
						
if (${USE_OPENGL})
	target_link_libraries(SimEngine
							libglew_shared
							Engine
							glfw 
							assimp
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(SimEngine
							#MatplotlibC++
							Python3::Python
							)
endif()
						
