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

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <itkImage.h>
#include <itkMedianImageFilter.h>
#include <itkOpenCVImageBridge.h>

// Process a single frame of video and return the resulting frame
cv::Mat processFrame( const cv::Mat& inputImage )
{
  const unsigned int Dimension =                   2;
  typedef unsigned char                            InputPixelType;
  typedef unsigned char                            OutputPixelType;
  typedef itk::Image< InputPixelType, Dimension >  InputImageType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;
  typedef itk::OpenCVImageBridge                   BridgeType;
  typedef itk::MedianImageFilter< InputImageType, OutputImageType > 
                                                   FilterType;

  FilterType::Pointer filter = FilterType::New();
  InputImageType::SizeType neighborhoodRadius;
  neighborhoodRadius[0] = 9;
  neighborhoodRadius[1] = 9;
  filter->SetRadius( neighborhoodRadius );

  InputImageType::Pointer itkFrame =
    BridgeType::CVMatToITKImage< InputImageType >( inputImage );

  filter->SetInput(itkFrame);
  try
    {
    filter->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    }

  return BridgeType::ITKImageToCVMat<OutputImageType>( filter->GetOutput(),
                                                       true );
}

// Iterate through a video, process each frame, and display the result in a GUI.
void processAndDisplayVideo(cv::VideoCapture& vidCap)
{
  double frameRate = vidCap.get( CV_CAP_PROP_FPS );
  int width = vidCap.get( CV_CAP_PROP_FRAME_WIDTH );
  int height = vidCap.get( CV_CAP_PROP_FRAME_HEIGHT );

  std::string windowName = "Exercise 2: Basic Video Filtering in OpenCV";
  cv::namedWindow( windowName, CV_WINDOW_FREERATIO);
  cvResizeWindow( windowName.c_str(), width, height+50 );

  unsigned delay = 1000 / frameRate;

  cv::Mat frame;
  while( vidCap.read(frame) )
  {
    cv::Mat outputFrame = processFrame( frame );
    cv::imshow( windowName, outputFrame );

    if( cv::waitKey(delay) >= 0 )
    {
      break;
    }
  }
}

// Iterate through a video, process each frame, and save the processed video.
void processAndSaveVideo(cv::VideoCapture& vidCap, const std::string& filename)
{
  double frameRate = vidCap.get( CV_CAP_PROP_FPS );
  int width = vidCap.get( CV_CAP_PROP_FRAME_WIDTH );
  int height = vidCap.get( CV_CAP_PROP_FRAME_HEIGHT );

  int fourcc = CV_FOURCC('D','I','V','X');
  
  cv::VideoWriter writer( filename, fourcc, frameRate,
                          cv::Size(width, height) );

  cv::Mat frame;
  while( vidCap.read(frame) )
  {
    cv::Mat outputFrame = processFrame( frame );
    writer << outputFrame;
  }
}

int main ( int argc, char **argv )
{
  if( argc < 2 )
  {
    std::cout << "Usage: "<< argv[0] <<" input_image output_image"<<std::endl;
    return -1;
  }

  cv::VideoCapture vidCap( argv[1] );
  if( !vidCap.isOpened() )
  {
    std::cerr << "Unable to open video file: "<< argv[1] << std::endl;
    return -1;
  }

  if(argc < 3)
  {
    processAndDisplayVideo( vidCap );
  }
  else
  {
    processAndSaveVideo( vidCap, argv[2] );
  }

  return 0;
}
