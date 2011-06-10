/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>


int main ( int argc, char **argv )
{
  // if there are no arguments then print usage and exit
  // Note: argv[0] is always set to the executable name
  if( argc < 2 )
  {
    std::cout << "Usage: "<< argv[0] <<" input_image output_image"<<std::endl;
    return -1;
  }

  // read the input image from the specified file
  cv::Mat inputImage = cv::imread( argv[1] );
  // create a matrix object to store the grayscale image
  cv::Mat grayImage;
  // create a matrix object to store the resulting image
  cv::Mat resultImage;
  // Convert the color image to grayscale because Canny requires grayscale
  cv::cvtColor(inputImage, grayImage, CV_BGR2GRAY);
  // apply Canny edge detection to the image
  cv::Canny( grayImage, resultImage, 128, 255 );

  // if there is only an input file specified then display the result on screen
  if(argc < 3)
  {
    // The title string for the GUI window
    std::string windowName = "Exercise 1: Basic Filtering in OpenCV";
    // create a window, CV_WINDOW_FREERATIO is needed for display with OpenGL
    cv::namedWindow( windowName, CV_WINDOW_FREERATIO);
    // show the image in the previously created window
    cv::imshow( windowName, resultImage );
    // wait for the user to press a key, then continue
    cv::waitKey();
  }
  // otherwise, write the resulting image to the specified output file.
  else
  {
    // write the resulting image to a file
    cv::imwrite( argv[2], resultImage );
  }

  return 0;
}

