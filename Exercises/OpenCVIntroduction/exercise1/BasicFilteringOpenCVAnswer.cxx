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
  if( argc < 2 )
  {
    std::cout << "Usage: "<< argv[0] <<" input_image output_image"<<std::endl;
    return -1;
  }

  cv::Mat inputImage = cv::imread( argv[1] );
  cv::Mat grayImage;
  cv::Mat resultImage;
  cv::cvtColor(inputImage, grayImage, CV_BGR2GRAY);
  cv::Canny( grayImage, resultImage, 128, 255 );

  if(argc < 3)
  {
    std::string windowName = "Exercise 1: Basic Filtering in OpenCV";
    cv::namedWindow( windowName, CV_WINDOW_FREERATIO);
    cv::imshow( windowName, resultImage );
    cv::waitKey();
  }
  else
  {
    cv::imwrite( argv[2], resultImage );
  }

  return 0;
}

