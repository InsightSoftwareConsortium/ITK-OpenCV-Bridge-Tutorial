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
#include <itkMedianImageFilter.h>
#include <itkImageFilterToVideoFilterWrapper.h>
#include <itkVideoFileReader.h>
#include <itkVideoFileWriter.h>
#include <itkOpenCVVideoIOFactory.h>

int main ( int argc, char **argv )
{
  if( argc < 3 )
    {
    std::cout << "Usage: " << argv[0] << "input_image output_image" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension =                         2;
  typedef unsigned char                                  PixelType;
  typedef itk::Image< PixelType, Dimension >             FrameType;
  typedef itk::VideoStream< FrameType >                  VideoType;

  typedef itk::VideoFileReader< VideoType >              ReaderType;
  typedef itk::VideoFileWriter< VideoType >              WriterType;
  typedef itk::MedianImageFilter< FrameType, FrameType > ImageFilterType;
  typedef itk::ImageFilterToVideoFilterWrapper< ImageFilterType >
                                                         VideoFilterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  VideoFilterType::Pointer videoFilter = VideoFilterType::New();

  itk::ObjectFactoryBase::RegisterFactory( itk::OpenCVVideoIOFactory::New() );
  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );

  FrameType::SizeType neighborhoodRadius;
  neighborhoodRadius[0] = 10;
  neighborhoodRadius[1] = 10;
  imageFilter->SetRadius( neighborhoodRadius );
  videoFilter->SetImageFilter( imageFilter );

  videoFilter->SetInput( reader->GetOutput() );
  writer->SetInput( videoFilter->GetOutput() );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

