file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_library(SmartEnergyAutoProgram SHARED ${source_files} ${hdrs})

set_target_properties(SmartEnergyAutoProgram PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartEnergyAutoProgram"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartEnergyAutoProgram"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartEnergyAutoProgram")

target_link_libraries(SmartEnergyAutoProgram SimEngine)

set_property(TARGET SmartEnergyAutoProgram PROPERTY FOLDER "DLLs")