#
# Make sure that we prefix the executable names with the exerciser number.
#

# BasicFilteringOpenCVBridge
add_executable(BasicFilteringOpenCVBridge 
  BasicFilteringOpenCVBridge.cxx )
target_link_libraries(BasicFilteringOpenCVBridge
  ${ITK_LIBRARIES} ${OpenCV_LIBS})

# BasicFilteringOpenCVBridgeAnswer
add_executable(BasicFilteringOpenCVBridgeAnswer 
  BasicFilteringOpenCVBridgeAnswer.cxx )
target_link_libraries(BasicFilteringOpenCVBridgeAnswer
  ${ITK_LIBRARIES} ${OpenCV_LIBS})
