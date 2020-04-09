file(GLOB_RECURSE engine_source "../Engine/*.cpp")
file(GLOB_RECURSE source_files "*.cpp")

add_executable(SmartHouse ${source_files} ${engine_source})

#target_link_libraries(SmartHouse glfw ${OPENGL_LIBRARIES})

add_definitions(-DGLEW_STATIC)
add_definitions(-DGLEW_NO_GLU)

target_link_libraries(SmartHouse
						pugixml 
						output_system
						libglew_static
						Core
						BulletDynamics
						BulletCollision
						LinearMath 
						glfw ${OPENGL_LIBRARIES})
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
