file(GLOB_RECURSE source_files "*.cpp")

add_executable(SimEngine ${source_files})

add_definitions(-DGLEW_NO_GLU)

target_link_libraries(SimEngine						
						Core
						pugixml 
						output_system
						)
						
if (${USE_OPENGL})
	target_link_libraries(SimEngine
							Engine
							glfw 
							libglewmx_static
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
						
