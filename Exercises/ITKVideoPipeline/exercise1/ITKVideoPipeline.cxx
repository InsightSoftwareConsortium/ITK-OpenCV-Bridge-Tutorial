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

#include <itkVideoStream.h>
#include <itkImageFilterToVideoFilterWrapper.h>
#include <itkMedianImageFilter.h>
#include <itkVideoFileReader.h>
#include <itkVideoFileWriter.h>
#include <itkOpenCVVideoIOFactory.h>

/**
 * Use ITK's Video pipeline to process a video using a median filter on each frame
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
  const unsigned int Dimension =                                    2;
  typedef unsigned char InputPixelType;
  typedef unsigned char OutputPixelType;
  typedef itk::Image< InputPixelType, Dimension > InputFrameType;
  typedef itk::Image< OutputPixelType, Dimension > OutputFrameType;
  typedef itk::VideoStream< InputFrameType > InputVideoType;
  typedef itk::VideoStream< OutputFrameType > OutputVideoType;
  typedef itk::MedianImageFilter< InputFrameType, OutputFrameType > ImageFilterType;
  typedef itk::ImageFilterToVideoFilterWrapper< ImageFilterType > VideoFilterType;
  typedef itk::VideoFileReader< InputVideoType > ReaderType;
  typedef itk::VideoFileWriter< OutputVideoType > WriterType;

  // Let the ITK IO factory know that we're using OpenCV for IO
  itk::ObjectFactoryBase::RegisterFactory( itk::OpenCVVideoIOFactory::New() );

  // Initialize the components of the pipeline
  ReaderType::Pointer reader = ReaderType::New();
  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  VideoFilterType::Pointer videoFilter = VideoFilterType::New();
  WriterType::Pointer writer = WriterType::New();

  // Set up the reader and writer
  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );

  // Set up the video filter
  InputFrameType::SizeType neighborhoodRadius;
  neighborhoodRadius[0] = 10;
  neighborhoodRadius[1] = 10;
  imageFilter->SetRadius( neighborhoodRadius );
  videoFilter->SetImageFilter( imageFilter );

  // Connect the pipeline
  videoFilter->SetInput( reader->GetOutput() );
  writer->SetInput( videoFilter->GetOutput() );

  // Call Update to execute the pipeline
  writer->Update();

  return 0;
}

