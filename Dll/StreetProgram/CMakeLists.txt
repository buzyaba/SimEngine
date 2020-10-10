file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_library(StreetProgram SHARED ${source_files} ${hdrs})

set_target_properties(StreetProgram PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetProgram"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetProgram"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetProgram")

target_link_libraries(StreetProgram SimEngine)

set_property(TARGET StreetProgram PROPERTY FOLDER "DLLs")