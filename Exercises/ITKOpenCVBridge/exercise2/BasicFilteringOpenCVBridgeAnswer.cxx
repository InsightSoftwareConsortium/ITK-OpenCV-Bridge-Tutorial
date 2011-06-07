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
#include <itkCurvatureFlowImageFilter.h>
#include <itkOpenCVImageBridge.h>

/**
 * Use OpenCV and ITK to apply a Curvature Flow filter to an image. Set the
 * TimeStep of the filter to 0.5 and the NumberOfIterations to 20.
 */
int main ( int argc, char **argv )
{

  // Check arguments
  if( argc < 3 )
    {
    std::cout << "Usage: " << argv[0] << " <input> <output>" << std::endl;
    return -1;
    }

  // Set up typedefs for ITK
  typedef unsigned char                                                    InputPixelType;
  typedef float                                                            OutputPixelType;
  const unsigned int Dimension =                                           2;
  typedef itk::Image< InputPixelType, Dimension >                          InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >                         OutputImageType;
  typedef itk::CurvatureFlowImageFilter< InputImageType, OutputImageType > FilterType;

  // Open thge file with OpenCV
  cv::Mat openCVImage = cv::imread( argv[1] );

  // Convert the image to ITK
  InputImageType::Pointer itkImage =
    itk::OpenCVImageBridge::CVMatToITKImage< InputImageType >( openCVImage );

  // Set up the ITK filter
  FilterType::Pointer filter = FilterType::New();
  filter->SetTimeStep( 0.5 );
  filter->SetNumberOfIterations( 20 );

  // Set the converted image as input and run the filter
  filter->SetInput( itkImage );
  filter->Update();

  // Convert back to OpenCV and write the image out
  cv::imwrite( argv[2],
    itk::OpenCVImageBridge::ITKImageToCVMat< OutputImageType >( filter->GetOutput() ) );


  return 0;
}

