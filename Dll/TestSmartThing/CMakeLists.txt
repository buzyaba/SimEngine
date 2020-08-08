
file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(TestSmartThing SHARED ${source_files} ${hdrs})


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(TestSmartThing
						BasicExamples
						)
						
if (${USE_OpenGL})
	target_link_libraries(TestSmartThing
							# Engine
							glfw 
							libglewmx_static
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(TestSmartThing
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET TestSmartThing PROPERTY FOLDER "DLLs") 						
	