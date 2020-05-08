#file(GLOB_RECURSE engine_source "../Engine/*.cpp")
file(GLOB hdrs "${CMAKE_SOURCE_DIR}/include/SmartHouse/*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_executable(SmartHouse ${source_files} ${engine_source})

#target_link_libraries(SmartHouse glfw ${OPENGL_LIBRARIES})

add_definitions(-DGLEW_NO_GLU)

target_link_libraries(SmartHouse
						Engine
						Core
						BasicExamples
						pugixml 
						output_system
						libglewmx_static						
						BulletDynamics
						BulletCollision
						LinearMath 
						glfw )
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(SmartHouse
							MatplotlibC++
							Python3::Python
							${OPENGL_LIBRARIES})
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
