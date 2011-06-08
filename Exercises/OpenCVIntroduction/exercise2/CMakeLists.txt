project( BasicVideoFilteringOpenCV )

find_package( OpenCV REQUIRED )

add_executable( BasicVideoFilteringOpenCV BasicVideoFilteringOpenCV.cxx )
target_link_libraries( BasicVideoFilteringOpenCV ${OpenCV_LIBS} )

add_executable( BasicVideoFilteringOpenCVAnswer BasicVideoFilteringOpenCVAnswer.cxx )
target_link_libraries( BasicVideoFilteringOpenCVAnswer ${OpenCV_LIBS} )
