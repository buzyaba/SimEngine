#file(GLOB_RECURSE engine_source "../Engine/*.cpp")
file(GLOB hdrs "${CMAKE_SOURCE_DIR}/include/SmartHouse/*.h*")
file(GLOB_RECURSE source_files "*.cpp")

file(GLOB TRAFFIC_SIM ${CMAKE_SOURCE_DIR}/src/TrafficSim/*.cpp)
list(REMOVE_ITEM TRAFFIC_SIM ${CMAKE_SOURCE_DIR}/src/TrafficSim/main.cpp)

add_executable(SmartHouse ${source_files} ${hdrs} ${TRAFFIC_SIM})

#target_link_libraries(SmartHouse glfw ${OPENGL_LIBRARIES})

add_definitions(-DGLEW_NO_GLU)

target_link_libraries(SmartHouse						
						Core
						BasicExamples
						pugixml 
						output_system
						)
						
if (${USE_OpenGL})
	target_link_libraries(SmartHouse
							# Engine
							glfw 
							libglewmx_static
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(SmartHouse
							#MatplotlibC++
							Python3::Python
							)
endif()
						
