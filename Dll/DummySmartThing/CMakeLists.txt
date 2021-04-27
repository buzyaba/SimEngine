file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(DummySmartThing SHARED ${source_files} ${hdrs})

set_target_properties(DummySmartThing PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TDummySmartThing"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TDummySmartThing"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TDummySmartThing")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(DummySmartThing
						SimEngine
						)
						
if (${USE_OPENGL})
	target_link_libraries(DummySmartThing
							glfw 
							libglew_shared
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET DummySmartThing PROPERTY FOLDER "DLLs")
