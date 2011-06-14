#
# Make sure that we prefix the executable names with the exerciser number.
#

# ITKVideoPipeline
add_executable(Ex2_ITKVideoPipeline 
  Ex2_ITKVideoPipeline.cxx )
target_link_libraries(Ex2_ITKVideoPipeline ${ITK_LIBRARIES})

# ITKVideoPipeline
add_executable(Ex2_ITKVideoPipelineAnswer 
  Ex2_ITKVideoPipelineAnswer.cxx )
target_link_libraries(Ex2_ITKVideoPipelineAnswer ${ITK_LIBRARIES})
