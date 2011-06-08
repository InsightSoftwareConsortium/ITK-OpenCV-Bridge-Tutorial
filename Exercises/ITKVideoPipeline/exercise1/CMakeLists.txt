#
# Make sure that we prefix the executable names with the exerciser number.
#

# ITKVideoPipeline
add_executable(Ex1_ITKVideoPipeline 
  ITKVideoPipeline.cxx )
target_link_libraries(Ex1_ITKVideoPipeline ${ITK_LIBRARIES})

# ITKVideoPipeline
add_executable(Ex1_ITKVideoPipelineAnswer 
  ITKVideoPipelineAnswer.cxx )
target_link_libraries(Ex1_ITKVideoPipelineAnswer ${ITK_LIBRARIES})
