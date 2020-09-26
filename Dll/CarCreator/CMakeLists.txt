file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(CarCreator SHARED ${source_files} ${hdrs})

set_target_properties(CarCreator PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TCarCreator"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TCarCreator"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TCarCreator")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(CarCreator
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(CarCreator
							# Engine
							glfw 
							libglewmx_static
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(CarCreator
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET CarCreator PROPERTY FOLDER "DLLs")