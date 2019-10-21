find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(TrafficSim mainTrafficSim.cpp TrafficSim.cpp)
add_executable(SmartHouse mainSmartHouse.cpp SmartHouse.cpp)
add_executable(test mainTest.cpp)

target_link_libraries(TrafficSim glfw ${OPENGL_LIBRARIES})
target_link_libraries(SmartHouse glfw ${OPENGL_LIBRARIES})

add_definitions(-DGLEW_STATIC)

target_link_libraries(TrafficSim libglew_static)
target_link_libraries(SmartHouse libglew_static)

target_link_libraries(test gtest)

