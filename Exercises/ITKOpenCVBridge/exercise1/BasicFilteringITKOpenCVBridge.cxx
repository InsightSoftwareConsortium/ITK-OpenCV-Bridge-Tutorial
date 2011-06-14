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

int main ( int argc, char **argv )
{
  if( argc < 2 )
  {
    std::cout << "Usage: "<< argv[0] <<" input_image output_image"<<std::endl;
    return -1;
  }

  cv::Mat inputImage = cv::imread( argv[1] );

  typedef unsigned char                            InputPixelType;
  typedef unsigned char                            OutputPixelType;
  const unsigned int Dimension =                   2;
  typedef itk::Image< InputPixelType, Dimension >  InputImageType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;
  typedef itk::OpenCVImageBridge                   BridgeType;
  typedef itk::MedianImageFilter< InputImageType, OutputImageType > 
                                                   FilterType;

  InputImageType::Pointer itkImage =
    BridgeType::CVMatToITKImage< InputImageType >( inputImage );

  FilterType::Pointer filter = FilterType::New();
  InputImageType::SizeType neighborhoodRadius;
  neighborhoodRadius[0] = 9;
  neighborhoodRadius[1] = 9;
  filter->SetRadius( neighborhoodRadius );

  filter->SetInput( itkImage );
  try
    {
    filter->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat resultImage =
    BridgeType::ITKImageToCVMat< OutputImageType >( filter->GetOutput() );

  if(argc < 3)
  {
    std::string windowName = "Exercise 1: Basic Filtering in OpenCV & ITK";
    cv::namedWindow( windowName, CV_WINDOW_FREERATIO);
    cvResizeWindow( windowName.c_str(), resultImage.cols, resultImage.rows+50 );
    cv::Mat scaled;
    resultImage.convertTo( scaled, CV_8UC1 );
    cv::imshow( windowName, scaled );
    cv::waitKey();
  }
  else
  {
    cv::imwrite( argv[2], resultImage );
  }

  return 0;
}
