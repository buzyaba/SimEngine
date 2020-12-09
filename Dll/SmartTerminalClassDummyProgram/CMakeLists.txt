file(GLOB hdrs "*.h*")
file(GLOB_RECURSE source_files "*.cpp")

add_library(SmartTerminalClassDummyProgram SHARED ${source_files} ${hdrs})

set_target_properties(SmartTerminalClassDummyProgram PROPERTIES
						LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartTerminalClassDummyProgram"
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartTerminalClassDummyProgram"
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/assets/management_programs/TSmartTerminalClassDummyProgram")

target_link_libraries(SmartTerminalClassDummyProgram SimEngine)

set_property(TARGET SmartTerminalClassDummyProgram PROPERTY FOLDER "DLLs")