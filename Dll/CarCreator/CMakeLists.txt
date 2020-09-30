file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(CarCreator SHARED ${source_files} ${hdrs} ${CMAKE_SOURCE_DIR}/Dll/Road/Road.hpp ${CMAKE_SOURCE_DIR}/Dll/Road/Road.cpp ${CMAKE_SOURCE_DIR}/Dll/Road/Car.hpp ${CMAKE_SOURCE_DIR}/Dll/Road/Car.cpp)

set_target_properties(CarCreator PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TCarCreator"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TCarCreator"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TCarCreator")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(CarCreator
						SimEngine
						)
						
if (${USE_OPENGL})
	target_link_libraries(CarCreator
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()

set_property(TARGET CarCreator PROPERTY FOLDER "DLLs")