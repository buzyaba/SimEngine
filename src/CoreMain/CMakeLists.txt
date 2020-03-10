# file(GLOB hdrs "*.h*") #��������� � ���������� hdrs ��� ����� � ����������� .h
# file(GLOB srcs "*.cpp")#��������� � ���������� srcs ��� ����� � ����������� .h

# find_package(OpenMP)
# if (OPENMP_FOUND)
#     set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#     set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# endif()

# add_executable(CoreMain ${srcs} ${hdrs})
# target_link_libraries(CoreMain 
# 						pugixml 
# 						output_system
# 						Core
# 						SmartHouseData
# 						TrafficSimData)

# #add_library(${MyLib1} STATIC ${srcs} ${hdrs}) #������� ����������� ���������� � ������ �� ���������� ${MyLib1}, ����������� � ������������ CMake ����� (��������� ���������� ����������� � �����������), � �� ����������� ����� �� ���������� ${srcs} � ${hdrs}


