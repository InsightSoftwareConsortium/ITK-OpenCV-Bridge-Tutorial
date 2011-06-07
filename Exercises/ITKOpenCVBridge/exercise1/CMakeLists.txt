#
# Make sure that we prefix the executable names with the exerciser number.
#
add_executable(BasicFilteringOpenCVBridgeAnswer 
  BasicFilteringOpenCVBridgeAnswer.cxx )
target_link_libraries(BasicFilteringOpenCVBridgeAnswer
  ${ITK_LIBRARIES} ${OpenCV_LIBS})