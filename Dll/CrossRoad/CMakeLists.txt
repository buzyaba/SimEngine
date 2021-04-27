file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(CrossRoad SHARED ${source_files} ${hdrs})

set_target_properties(CrossRoad PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TCrossRoad"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TCrossRoad"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TCrossRoad")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(CrossRoad
						SimEngine
						)
						
if (${USE_OPENGL})
	target_link_libraries(CrossRoad
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET CrossRoad PROPERTY FOLDER "DLLs")