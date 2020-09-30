file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(Room SHARED ${source_files} ${hdrs})

set_target_properties(Room PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TRoom"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TRoom"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TRoom")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(Room
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(Room
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET Room PROPERTY FOLDER "DLLs")