file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

file(GLOB xroad_hdrs "${CMAKE_SOURCE_DIR}/Dll/CrossRoad/*.h*")
file(GLOB xroad_src "${CMAKE_SOURCE_DIR}/Dll/CrossRoad/*.cpp")
list(REMOVE_ITEM xroad_src "${CMAKE_SOURCE_DIR}/Dll/CrossRoad/CrossRoadCreator.cpp")

add_library(CarManager SHARED ${source_files} ${hdrs} ${xroad_hdrs} ${xroad_src})

set_target_properties(CarManager PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TCarManager"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TCarManager"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TCarManager")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(CarManager
						SimEngine
						)
						
if (${USE_OPENGL})
	target_link_libraries(CarManager
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET CarManager PROPERTY FOLDER "DLLs")