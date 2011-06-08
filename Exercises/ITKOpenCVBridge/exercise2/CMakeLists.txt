#
# Make sure that we prefix the executable names with the exerciser number.
#

# BasicFilteringOpenCVBridge
add_executable(Ex2_BasicFilteringOpenCVBridge 
  BasicFilteringOpenCVBridge.cxx )
target_link_libraries(Ex2_BasicFilteringOpenCVBridge
  ${ITK_LIBRARIES} ${OpenCV_LIBS})

# BasicFilteringOpenCVBridgeAnswer
add_executable(Ex2_BasicFilteringOpenCVBridgeAnswer 
  BasicFilteringOpenCVBridgeAnswer.cxx )
target_link_libraries(Ex2_BasicFilteringOpenCVBridgeAnswer
  ${ITK_LIBRARIES} ${OpenCV_LIBS})
