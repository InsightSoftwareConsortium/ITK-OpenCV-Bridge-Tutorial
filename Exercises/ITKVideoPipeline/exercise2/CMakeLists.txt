#
# Make sure that we prefix the executable names with the exerciser number.
#

# ITKVideoPipeline
add_executable(ITKVideoMultiFrameFilters 
  ITKVideoMultiFrameFilters.cxx )
target_link_libraries(ITKVideoMultiFrameFilters ${ITK_LIBRARIES})

# ITKVideoPipeline
add_executable(ITKVideoMultiFrameFiltersAnswer 
  ITKVideoMultiFrameFiltersAnswer.cxx )
target_link_libraries(ITKVideoMultiFrameFiltersAnswer ${ITK_LIBRARIES})
