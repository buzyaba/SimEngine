file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_library(StreetAutoProgram SHARED ${source_files} ${hdrs})

set_target_properties(StreetAutoProgram PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetAutoProgram"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetAutoProgram"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/management_programs/TStreetAutoProgram")

target_link_libraries(StreetAutoProgram SimEngine)

set_property(TARGET StreetAutoProgram PROPERTY FOLDER "DLLs")