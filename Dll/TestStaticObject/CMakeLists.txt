
file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(TestStaticObject SHARED ${source_files} ${hdrs})


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(TestStaticObject
						BasicExamples
						)
						
if (${USE_OpenGL})
	target_link_libraries(TestStaticObject
							Engine
							glfw 
							libglewmx_static						
							BulletDynamics
							BulletCollision
							LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(TestStaticObject
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET TestStaticObject PROPERTY FOLDER "DLLs") 						
						
#if (WIN32)
#    target_link_libraries(TrafficSim 
#        ${CMAKE_SOURCE_DIR}/build/lib/Debug/BulletDynamics_Debug.lib
#        ${CMAKE_SOURCE_DIR}/build/lib/Debug/BulletCollision_Debug.lib
#        ${CMAKE_SOURCE_DIR}/build/lib/Debug/LinearMath_Debug.lib)
#else ()
#    target_link_libraries(TrafficSim 
#        ${CMAKE_SOURCE_DIR}/build/lib/bulletphys/src/BulletDynamics/libBulletDynamics.a
#        ${CMAKE_SOURCE_DIR}/build/lib/bulletphys/src/BulletCollision/libBulletCollision.a
#        ${CMAKE_SOURCE_DIR}/build/lib/bulletphys/src/LinearMath/libLinearMath.a)
#endif(WIN32)
