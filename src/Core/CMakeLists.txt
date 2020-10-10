file(GLOB hdrs "${CMAKE_SOURCE_DIR}/include/Core/*.h*")

file(GLOB srcs "*.cpp")

add_definitions(-DGLEW_NO_GLU)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_library(Core STATIC ${srcs} ${hdrs}) 

