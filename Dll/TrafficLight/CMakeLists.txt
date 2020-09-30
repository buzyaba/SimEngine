file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(TrafficLight SHARED ${source_files} ${hdrs})

set_target_properties(TrafficLight PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TTrafficLight"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TTrafficLight"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TTrafficLight")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(TrafficLight
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(TrafficLight
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(TrafficLight
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET TrafficLight PROPERTY FOLDER "DLLs")