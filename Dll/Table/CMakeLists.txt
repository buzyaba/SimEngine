file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(Table SHARED ${source_files} ${hdrs})

set_target_properties(Table PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TTable"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TTable"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TTable")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(Table
						SimEngine
						)
						
if (${USE_OPENGL})
	target_link_libraries(Table
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET Table PROPERTY FOLDER "DLLs")