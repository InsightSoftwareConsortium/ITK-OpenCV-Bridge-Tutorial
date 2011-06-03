project( HelloWorldOpenCV )

find_package( OpenCV REQUIRED )

add_executable( HelloWorldOpenCV HelloWorldOpenCV.cxx )

target_link_libraries( HelloWorldOpenCV ${OpenCV_LIBS} )
