
file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(TestObjectOfObservation SHARED ${source_files} ${hdrs})


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(TestObjectOfObservation
						Core
						)
						
if (${USE_OpenGL})
	target_link_libraries(TestObjectOfObservation
							# Engine
							glfw 
							libglewmx_static
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(TestObjectOfObservation
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET TestObjectOfObservation PROPERTY FOLDER "DLLs") 		