file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(DummyObject SHARED ${source_files} ${hdrs})

set_target_properties(DummyObject PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TDummyObject"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TDummyObject"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TDummyObject")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(DummyObject
						SimEngine
						)
						
if (${USE_OPENGL})
	target_link_libraries(DummyObject
							glfw 
							libglew_shared
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET DummyObject PROPERTY FOLDER "DLLs")
