
file(GLOB_RECURSE engine_source "../Engine/*.cpp")
file(GLOB_RECURSE source_files "*.cpp")

add_executable(SmartHouse ${source_files} ${engine_source})

target_link_libraries(SmartHouse glfw ${OPENGL_LIBRARIES})

add_definitions(-DGLEW_STATIC)

target_link_libraries(SmartHouse libglew_static)
target_link_libraries(SmartHouse 
    ${CMAKE_SOURCE_DIR}/build/lib/bulletphys/src/BulletDynamics/libBulletDynamics.a
    ${CMAKE_SOURCE_DIR}/build/lib/bulletphys/src/BulletCollision/libBulletCollision.a
    ${CMAKE_SOURCE_DIR}/build/lib/bulletphys/src/LinearMath/libLinearMath.a
   )
