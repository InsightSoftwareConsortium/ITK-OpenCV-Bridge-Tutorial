project( HelloWorldOpenCV )

find_package( OpenCV REQUIRED )

add_executable( BasicFilteringOpenCV BasicFilteringOpenCV.cxx )
target_link_libraries( BasicFilteringOpenCV ${OpenCV_LIBS} )

add_executable( BasicFilteringOpenCVAnswer BasicFilteringOpenCVAnswer.cxx )
target_link_libraries( BasicFilteringOpenCVAnswer ${OpenCV_LIBS} )
