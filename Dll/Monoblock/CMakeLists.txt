file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(Monoblock SHARED ${source_files} ${hdrs})

set_target_properties(Monoblock PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TMonoblock"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TMonoblock"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TMonoblock")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(Monoblock
						SimEngine
						)
						
if (${USE_OPENGL})
	target_link_libraries(Monoblock
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET Monoblock PROPERTY FOLDER "DLLs")