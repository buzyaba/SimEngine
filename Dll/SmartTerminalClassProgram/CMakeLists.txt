file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_library(SmartTerminalClassProgram SHARED ${source_files} ${hdrs})

set_target_properties(SmartTerminalClassProgram PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartTerminalClassProgram"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartTerminalClassProgram"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartTerminalClassProgram")

target_link_libraries(SmartTerminalClassProgram SimEngine)

set_property(TARGET SmartTerminalClassProgram PROPERTY FOLDER "DLLs")