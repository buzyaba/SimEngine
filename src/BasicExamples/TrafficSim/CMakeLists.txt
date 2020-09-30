# file(GLOB hdrs "${CMAKE_SOURCE_DIR}/include/BasicExamples/TrafficSim/*.h*")
# file(GLOB_RECURSE source_files "*.cpp")

# file(GLOB SMART_HOUSE ${CMAKE_SOURCE_DIR}/src/BasicExamples/SmartHouse/*.cpp)
# list(REMOVE_ITEM SMART_HOUSE ${CMAKE_SOURCE_DIR}/src/BasicExamples/SmartHouse/main.cpp)

# add_executable(TrafficSim ${source_files} ${hdrs} ${SMART_HOUSE})


# add_definitions(-DGLEW_NO_GLU)

# target_link_libraries(TrafficSim					
# 						Core
# 						pugixml 
# 						output_system
# 						)
						
# if (${USE_OPENGL})
# 	target_link_libraries(TrafficSim
# 							Engine
# 							glfw 
# 							libglewmx_static
# 							assimp
# 							# LinearMath 
# 							${OPENGL_LIBRARIES}
# 	)
# endif()
