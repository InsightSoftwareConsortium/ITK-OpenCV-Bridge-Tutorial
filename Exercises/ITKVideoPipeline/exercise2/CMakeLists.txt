#
# Make sure that we prefix the executable names with the exerciser number.
#

# ITKVideoPipeline
add_executable(ITKVideoMultiFrameFilters 
  ITKVideoMultiFrameFilters.cxx )
target_link_libraries(ITKVideoMultiFrameFilters ${ITK_LIBRARIES} ${OpenCV_LIBS})

# ITKVideoPipeline
add_executable(ITKVideoMultiFrameFiltersAnswer 
  ITKVideoMultiFrameFiltersAnswer.cxx )
target_link_libraries(ITKVideoMultiFrameFiltersAnswer ${ITK_LIBRARIES} ${OpenCV_LIBS})

# ITKVideoPipelineAnswer2
add_executable(ITKVideoMultiFrameFiltersAnswer2
  ITKVideoMultiFrameFiltersAnswer2.cxx )
target_link_libraries(ITKVideoMultiFrameFiltersAnswer2 ${ITK_LIBRARIES} ${OpenCV_LIBS})
