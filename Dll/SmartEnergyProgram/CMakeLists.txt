file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_library(SmartEnergyProgram SHARED ${source_files} ${hdrs})

set_target_properties(SmartEnergyProgram PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartEnergyProgram"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartEnergyProgram"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartEnergyProgram")

target_link_libraries(SmartEnergyProgram SimEngine)

set_property(TARGET SmartEnergyProgram PROPERTY FOLDER "DLLs")