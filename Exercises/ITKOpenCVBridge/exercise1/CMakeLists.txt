#
# Make sure that we prefix the executable names with the exerciser number.
#

# BasicFilteringOpenCVBridge
add_executable(Ex1_BasicFilteringOpenCVBridge 
  Ex1_BasicFilteringOpenCVBridge.cxx )
target_link_libraries(Ex1_BasicFilteringOpenCVBridge
  ${ITK_LIBRARIES} ${OpenCV_LIBS})

# BasicFilteringOpenCVBridgeAnswer
add_executable(Ex1_BasicFilteringOpenCVBridgeAnswer 
  Ex1_BasicFilteringOpenCVBridgeAnswer.cxx )
target_link_libraries(Ex1_BasicFilteringOpenCVBridgeAnswer
  ${ITK_LIBRARIES} ${OpenCV_LIBS})
