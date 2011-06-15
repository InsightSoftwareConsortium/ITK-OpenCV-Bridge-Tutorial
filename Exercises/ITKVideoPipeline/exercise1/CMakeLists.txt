#
# Make sure that we prefix the executable names with the exerciser number.
#

# ITKVideoPipeline
add_executable(ITKVideoSingleFrameFilters 
  ITKVideoSingleFrameFilters.cxx )
target_link_libraries(ITKVideoSingleFrameFilters ${ITK_LIBRARIES})

# ITKVideoPipeline
add_executable(ITKVideoSingleFrameFiltersAnswer 
  ITKVideoSingleFrameFiltersAnswer.cxx )
target_link_libraries(ITKVideoSingleFrameFiltersAnswer ${ITK_LIBRARIES})
