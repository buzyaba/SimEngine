file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(Road SHARED ${source_files} ${hdrs})

set_target_properties(Road PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TRoad"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TRoad"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TRoad")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(Road
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(Road
							# Engine
							glfw 
							libglewmx_static
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(Road
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET Road PROPERTY FOLDER "DLLs")