find_package(ITK REQUIRED )
if(ITK_FOUND)
  include(${USE_ITK_FILE})
endif()

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

add_subdirectory(exercise1)
add_subdirectory(exercise2)
