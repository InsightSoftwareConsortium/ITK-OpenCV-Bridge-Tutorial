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

#include <iostream>

#include <highgui.h>

#include <itkImage.h>
#include <itkMedianImageFilter.h>
#include <itkOpenCVImageBridge.h>

/**
 * Using OpenCV and ITK, open a video (cv), apply a Median filter to each frame
 * (itk) and write it back out (cv).
 */
int main ( int argc, char **argv )
{
  // Check arguments
  if( argc < 3 )
    {
    std::cout << "Usage: " << argv[0] << " <input> <output>" << std::endl;
    return -1;
    }

  // Open thge file with OpenCV
  cv::VideoCapture cap( argv[1] );
  if (!cap.isOpened())
    {
    std::cout << "Failed to open video from " << argv[1] << std::endl;
    return -1;
    }

  // Set up parameters for writer
  int fourcc = CV_FOURCC( 'M','P','4','2' );
  double fps = cap.get( CV_CAP_PROP_FPS );
  int width = static_cast<int>( cap.get( CV_CAP_PROP_FRAME_WIDTH ) );
  int height = static_cast<int>( cap.get( CV_CAP_PROP_FRAME_HEIGHT ) );

  // Set up writer
  cv::VideoWriter writer( std::string(argv[2]), fourcc, fps, cv::Size(width, height));


  // Set up typedefs for ITK
  const unsigned int Dimension =                                    2;
  typedef unsigned char                                             InputPixelType;
  typedef unsigned char                                             OutputPixelType;
  typedef itk::Image< InputPixelType, Dimension >                   InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >                  OutputImageType;
  typedef itk::MedianImageFilter< InputImageType, OutputImageType > FilterType;

  // Set up ITK filter
  FilterType::Pointer filter = FilterType::New();
  InputImageType::SizeType neighborhoodRadius;
  neighborhoodRadius[0] = 10;
  neighborhoodRadius[1] = 10;
  filter->SetRadius( neighborhoodRadius );

  // Loop through the frames of the video and apply the filter using ITK
  cv::Mat frame;
  while(cap.grab() && cap.retrieve(frame))
    {
    // Convert the frame to ITK
    InputImageType::Pointer itkFrame =
      itk::OpenCVImageBridge::CVMatToITKImage< InputImageType >( frame );

    // Filter the frame
    filter->SetInput(itkFrame);
    filter->Update();

    // Write the frame out
    writer << itk::OpenCVImageBridge::ITKImageToCVMat< OutputImageType >( filter->GetOutput(), true );
    }

  return 0;
}

