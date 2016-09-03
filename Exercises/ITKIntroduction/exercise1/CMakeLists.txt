cmake_minimum_required(VERSION 2.4)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

project(ITKBasicImageFiltering)

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

add_executable(BasicImageFilteringITK BasicImageFilteringITK.cxx )
target_link_libraries(BasicImageFilteringITK ${ITK_LIBRARIES})

add_executable(BasicImageFilteringITKAnswer1 BasicImageFilteringITKAnswer1.cxx )
target_link_libraries(BasicImageFilteringITKAnswer1 ${ITK_LIBRARIES})

add_executable(BasicImageFilteringITKAnswer2 BasicImageFilteringITKAnswer2.cxx )
target_link_libraries(BasicImageFilteringITKAnswer2 ${ITK_LIBRARIES})
