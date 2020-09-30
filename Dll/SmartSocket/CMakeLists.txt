file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(SmartSocket SHARED ${source_files} ${hdrs})

set_target_properties(SmartSocket PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TSmartSocket"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TSmartSocket"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TSmartSocket")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(SmartSocket
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(SmartSocket
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET SmartSocket PROPERTY FOLDER "DLLs")