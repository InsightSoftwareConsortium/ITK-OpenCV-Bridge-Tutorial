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
#include <itkCurvatureFlowImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkImageFilterToVideoFilterWrapper.h>
#include <itkFrameDifferenceVideoFilter.h>
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

  const unsigned int Dimension =                 2;
  typedef unsigned char                          IOPixelType;
  typedef float                                  RealPixelType;
  typedef itk::Image< IOPixelType, Dimension >   IOFrameType;
  typedef itk::Image< RealPixelType, Dimension > RealFrameType;
  typedef itk::VideoStream< IOFrameType >        IOVideoType;
  typedef itk::VideoStream< RealFrameType >      RealVideoType;

  typedef itk::VideoFileReader< IOVideoType >    ReaderType;
  typedef itk::VideoFileWriter< IOVideoType >    WriterType;
  typedef itk::CastImageFilter< RealFrameType, IOFrameType >
                                                 CastImageFilterType;
  typedef itk::ImageFilterToVideoFilterWrapper< CastImageFilterType >
                                                 CastVideoFilterType;
  typedef itk::CurvatureFlowImageFilter< IOFrameType, RealFrameType >
                                                 ImageFilterType;
  typedef itk::ImageFilterToVideoFilterWrapper< ImageFilterType >
                                                 VideoFilterType;

  typedef itk::FrameDifferenceVideoFilter< IOVideoType, IOVideoType >
                                                 FrameDifferenceFilterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  VideoFilterType::Pointer videoFilter = VideoFilterType::New();
  CastImageFilterType::Pointer imageCaster = CastImageFilterType::New();
  CastVideoFilterType::Pointer videoCaster = CastVideoFilterType::New();
  FrameDifferenceFilterType::Pointer frameDifferenceFilter =
    FrameDifferenceFilterType::New();

  itk::ObjectFactoryBase::RegisterFactory( itk::OpenCVVideoIOFactory::New() );
  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );

  frameDifferenceFilter->SetFrameOffset(1);

  videoCaster->SetImageFilter( imageCaster );

  imageFilter->SetTimeStep( 0.5 );
  imageFilter->SetNumberOfIterations( 20 );
  videoFilter->SetImageFilter( imageFilter );

  videoFilter->SetInput( reader->GetOutput() );
  videoCaster->SetInput( videoFilter->GetOutput() );
  frameDifferenceFilter->SetInput( videoCaster->GetOutput() );
  writer->SetInput( frameDifferenceFilter->GetOutput() );

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

