file(GLOB_RECURSE source_files "*.cpp")

add_executable(SimEngineLauncher ${source_files})

add_definitions(-DGLEW_NO_GLU)

target_link_libraries(SimEngineLauncher						
						Core
						SimEngine
						pugixml 
						output_system
						)
						
if (${USE_OPENGL})
	target_link_libraries(SimEngineLauncher
							libglew_shared
							Engine
							glfw 
							assimp
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
