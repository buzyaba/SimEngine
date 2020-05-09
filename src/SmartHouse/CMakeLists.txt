#file(GLOB_RECURSE engine_source "../Engine/*.cpp")
file(GLOB hdrs "${CMAKE_SOURCE_DIR}/include/SmartHouse/*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_executable(SmartHouse ${source_files} ${hdrs})

#target_link_libraries(SmartHouse glfw ${OPENGL_LIBRARIES})

add_definitions(-DGLEW_NO_GLU)

target_link_libraries(SmartHouse						
						Core
						BasicExamples
						pugixml 
						output_system
						)
						
if (${USE_OpenGL})
	target_link_libraries(SmartHouse
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
	target_link_libraries(SmartHouse
							MatplotlibC++
							Python3::Python
							)
endif()
						
						
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
