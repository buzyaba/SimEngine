file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_library(SmartHouseProgram SHARED ${source_files} ${hdrs})

set_target_properties(SmartHouseProgram PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartHouseProgram"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartHouseProgram"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartHouseProgram")

target_link_libraries(SmartHouseProgram SimEngine)

set_property(TARGET SmartHouseProgram PROPERTY FOLDER "DLLs")