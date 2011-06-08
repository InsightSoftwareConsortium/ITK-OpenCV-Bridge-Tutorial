find_package(ITK REQUIRED )
if(ITK_FOUND)
  include(${USE_ITK_FILE})
endif()

add_subdirectory(exercise1)
