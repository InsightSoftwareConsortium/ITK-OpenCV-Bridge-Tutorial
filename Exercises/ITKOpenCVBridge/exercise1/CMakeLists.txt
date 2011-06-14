
# BasicFilteringITKOpenCVBridge
add_executable(BasicFilteringITKOpenCVBridge 
  BasicFilteringITKOpenCVBridge.cxx )
target_link_libraries(BasicFilteringITKOpenCVBridge
  ${ITK_LIBRARIES} ${OpenCV_LIBS})

# BasicFilteringITKOpenCVBridgeAnswer
add_executable(BasicFilteringITKOpenCVBridgeAnswer 
  BasicFilteringITKOpenCVBridgeAnswer.cxx )
target_link_libraries(BasicFilteringITKOpenCVBridgeAnswer
  ${ITK_LIBRARIES} ${OpenCV_LIBS})
