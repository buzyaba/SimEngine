file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_library(StreetPeakProgram SHARED ${source_files} ${hdrs})

set_target_properties(StreetPeakProgram PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetPeakProgram"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetPeakProgram"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetPeakProgram")

target_link_libraries(StreetPeakProgram SimEngine)

set_property(TARGET StreetPeakProgram PROPERTY FOLDER "DLLs")