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
#include <itkRGBPixel.h>
#include <itkCurvatureFlowImageFilter.h>
#include <itkOpenCVImageBridge.h>

/**
 * Using OpenCV and ITK, open a video (cv), apply a Curvature Flow filter to
 * each frame (itk) and write it back out (cv).
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
  const unsigned int Dimension =                                           2;
  typedef unsigned char                                                    InputPixelType;
  typedef float                                                            OutputPixelType;
  typedef itk::Image< InputPixelType, Dimension >                          InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >                         OutputImageType;
  typedef itk::CurvatureFlowImageFilter< InputImageType, OutputImageType > FilterType;

  // Set up ITK filters
  FilterType::Pointer filter = FilterType::New();
  filter->SetTimeStep( 0.5 );
  filter->SetNumberOfIterations( 20 );

  // Loop through the frames of the video and apply the filter using ITK
  cv::Mat frameIn;
  cv::Mat frameOut;
  while( cap.grab() && cap.retrieve(frameIn) )
    {
    // Convert the frame to ITK
    InputImageType::Pointer itkFrame =
      itk::OpenCVImageBridge::CVMatToITKImage< InputImageType >( frameIn );

    // Filter the frame and cast to writable pixel type
    filter->SetInput(itkFrame);
    filter->Update();

    // Convert the frame back to OpenCV and force the output to have 3 channels
    frameOut = itk::OpenCVImageBridge::ITKImageToCVMat< OutputImageType >( filter->GetOutput(), true );

    // Convert the data to unsigned char so it can be written
    frameOut.convertTo( frameOut, CV_8U );

    // Write the frame out
    writer << frameOut;
    }

  return 0;
}

