file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(DummyStaticObject SHARED ${source_files} ${hdrs})

set_target_properties(DummyStaticObject PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TDummyStaticObject"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TDummyStaticObject"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TDummyStaticObject")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(DummyStaticObject
						SimEngine
						)
						
if (${USE_OPENGL})
	target_link_libraries(DummyStaticObject
							glfw 
							libglew_shared
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET DummyStaticObject PROPERTY FOLDER "DLLs")
