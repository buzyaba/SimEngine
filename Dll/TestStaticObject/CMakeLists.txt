
# file(GLOB hdrs "*.h*")
# file(GLOB_RECURSE source_files "*.cpp")


# # add_library(TestStaticObject SHARED ${source_files} ${hdrs})


# add_definitions(-DGLEW_NO_GLU)

# target_link_libraries(TestStaticObject
# 						Core
# 						)
						
# if (${USE_OPENGL})
# 	target_link_libraries(TestStaticObject
# 							# Engine
# 							glfw 
# 							libglew_shared
# 							# LinearMath 
# 							${OPENGL_LIBRARIES}
# 	)
# endif()
						
						
# if (${BUILD_PLOTTER})
# 	target_link_libraries(TestStaticObject
# 							MatplotlibC++
# 							Python3::Python
# 							)
# endif()

# set_property(TARGET TestStaticObject PROPERTY FOLDER "DLLs") 						
		
