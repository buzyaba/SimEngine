file(GLOB hdrs "${CMAKE_SOURCE_DIR}/include/TrafficSim/*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_executable(TrafficSim ${source_files} ${hdrs})


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(TrafficSim						
						Core
						BasicExamples
						pugixml 
						output_system
						)
						
if (${USE_OpenGL})
	target_link_libraries(TrafficSim
							Engine
							glfw 
							libglewmx_static						
							BulletDynamics
							BulletCollision
							LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(TrafficSim
							MatplotlibC++
							Python3::Python
							)
endif()
