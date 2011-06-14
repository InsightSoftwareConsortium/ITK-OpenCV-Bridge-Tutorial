
# BasicVideoFilteringITKOpenCVBridge
add_executable(BasicVideoFilteringITKOpenCVBridge 
  BasicVideoFilteringITKOpenCVBridge.cxx )
target_link_libraries(BasicVideoFilteringITKOpenCVBridge
  ${ITK_LIBRARIES} ${OpenCV_LIBS})

# BasicVideoFilteringITKOpenCVBridgeAnswer
add_executable(BasicVideoFilteringITKOpenCVBridgeAnswer 
  BasicVideoFilteringITKOpenCVBridgeAnswer.cxx )
target_link_libraries(BasicVideoFilteringITKOpenCVBridgeAnswer
  ${ITK_LIBRARIES} ${OpenCV_LIBS})
