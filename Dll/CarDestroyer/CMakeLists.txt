file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")


add_library(CarDestroyer SHARED ${source_files} ${hdrs} ${CMAKE_SOURCE_DIR}/Dll/Road/Road.hpp ${CMAKE_SOURCE_DIR}/Dll/Road/Road.cpp ${CMAKE_SOURCE_DIR}/Dll/Road/Car.hpp ${CMAKE_SOURCE_DIR}/Dll/Road/Car.cpp)

set_target_properties(CarDestroyer PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/models/TCarDestroyer"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/models/TCarDestroyer"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/models/TCarDestroyer")


add_definitions(-DGLEW_NO_GLU)

target_link_libraries(CarDestroyer
						Core
						)
						
if (${USE_OPENGL})
	target_link_libraries(CarDestroyer
							# Engine
							glfw 
							libglew_shared
							# LinearMath 
							${OPENGL_LIBRARIES}
	)
endif()
						
						
if (${BUILD_PLOTTER})
	target_link_libraries(CarDestroyer
							MatplotlibC++
							Python3::Python
							)
endif()

set_property(TARGET CarDestroyer PROPERTY FOLDER "DLLs")