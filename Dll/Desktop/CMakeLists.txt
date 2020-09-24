file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(Desktop SHARED ${source_files} ${hdrs})

set_target_properties(Desktop PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TDesktop"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TDesktop"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TDesktop")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(Desktop
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(Desktop
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(Desktop
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET Desktop PROPERTY FOLDER "DLLs")