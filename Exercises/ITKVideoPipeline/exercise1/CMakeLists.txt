#
# Make sure that we prefix the executable names with the exerciser number.
#

# ITKVideoPipeline
add_executable(Ex1_ITKVideoPipeline 
  Ex1_ITKVideoPipeline.cxx )
target_link_libraries(Ex1_ITKVideoPipeline ${ITK_LIBRARIES})

# ITKVideoPipeline
add_executable(Ex1_ITKVideoPipelineAnswer 
  Ex1_ITKVideoPipelineAnswer.cxx )
target_link_libraries(Ex1_ITKVideoPipelineAnswer ${ITK_LIBRARIES})
