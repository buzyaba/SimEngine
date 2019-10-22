
file(GLOB_RECURSE engine_source "../Engine/*.cpp")
file(GLOB_RECURSE source_files "*.cpp")

add_executable(SmartHouse ${source_files} ${engine_source})

target_link_libraries(SmartHouse glfw ${OPENGL_LIBRARIES})

add_definitions(-DGLEW_STATIC)

target_link_libraries(SmartHouse libglew_static)

