cmake_minimum_required(VERSION 2.4)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

project(ITKBasicImageFiltering)

find_package(ITK REQUIRED)

add_executable(BasicImageFilteringITK BasicImageFilteringITK.cxx )
target_link_libraries(BasicImageFilteringITK ${ITK_LIBRARIES})
