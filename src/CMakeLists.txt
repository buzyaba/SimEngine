find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

if(WIN32)
    add_executable(TrafficSim WIN32 mainTrafficSim.cpp TrafficSim.cpp)
else()
    add_executable(TrafficSim mainTrafficSim.cpp TrafficSim.cpp)
endif()

if(WIN32)
    add_executable(SmartHouse WIN32 mainSmartHouse.cpp SmartHouse.cpp)
else()
    add_executable(SmartHouse WIN32 mainSmartHouse.cpp SmartHouse.cpp)
endif()

target_link_libraries(TrafficSim glfw ${OPENGL_LIBRARIES})
target_link_libraries(SmartHouse glfw ${OPENGL_LIBRARIES})

add_definitions(-DGLEW_STATIC)

target_link_libraries(TrafficSim libglew_static)
target_link_libraries(SmartHouse libglew_static)

