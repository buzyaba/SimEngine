file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(Street SHARED ${source_files} ${hdrs})

set_target_properties(Street PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TStreet"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TStreet"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TStreet")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(Street
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(Street
							# Engine
							glfw 
							libglewmx_static
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(Street
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET Street PROPERTY FOLDER "DLLs")