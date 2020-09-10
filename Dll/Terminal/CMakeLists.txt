file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(Terminal SHARED ${source_files} ${hdrs})

set_target_properties(Terminal PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TTerminal"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TTerminal"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TTerminal")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(Terminal
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(Terminal
							# Engine
							glfw 
							libglewmx_static
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(Terminal
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET Terminal PROPERTY FOLDER "DLLs")