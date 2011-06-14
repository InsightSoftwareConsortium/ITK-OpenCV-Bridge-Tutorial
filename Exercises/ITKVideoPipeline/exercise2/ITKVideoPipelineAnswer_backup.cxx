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
#include <itkCannyEdgeDetectionImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkFrameAverageVideoFilter.h>
#include <itkVideoFileReader.h>
#include <itkVideoFileWriter.h>
#include <itkOpenCVVideoIOFactory.h>

//DEBUG
#include "itkTemporalRegion.h"

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
  const unsigned int Dimension =                                             2;
  typedef unsigned char                                                      IOPixelType;
  typedef float                                                              RealPixelType;
  typedef itk::Image< IOPixelType, Dimension >                               IOFrameType;
  typedef itk::Image< RealPixelType, Dimension >                             RealFrameType;
  typedef itk::VideoStream< IOFrameType >                                    IOVideoType;
  typedef itk::VideoStream< RealFrameType >                                  RealVideoType;
  typedef itk::CannyEdgeDetectionImageFilter< RealFrameType, RealFrameType > ImageFilterType;
  typedef itk::ImageFilterToVideoFilterWrapper< ImageFilterType >            VideoFilterType;
  typedef itk::CastImageFilter< IOFrameType, RealFrameType >                 CastImageFilterType;
  typedef itk::ImageFilterToVideoFilterWrapper< CastImageFilterType >        CastVideoFilterType;
  typedef itk::RescaleIntensityImageFilter< RealFrameType, IOFrameType >     RescaleImageFilterType;
  typedef itk::ImageFilterToVideoFilterWrapper< RescaleImageFilterType >     RescaleVideoFilterType;
  typedef itk::FrameAverageVideoFilter< IOVideoType, IOVideoType >           FrameAverageFilterType;
  //typedef itk::FrameAverageVideoFilter< RealVideoType, RealVideoType >           FrameAverageFilterType;
  typedef itk::VideoFileReader< IOVideoType >                                ReaderType;
  typedef itk::VideoFileWriter< IOVideoType >                                WriterType;

  // Let the ITK IO factory know that we're using OpenCV for IO
  itk::ObjectFactoryBase::RegisterFactory( itk::OpenCVVideoIOFactory::New() );

  // Initialize the components of the pipeline
  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  VideoFilterType::Pointer videoFilter = VideoFilterType::New();
  CastImageFilterType::Pointer imageCaster = CastImageFilterType::New();
  CastVideoFilterType::Pointer videoCaster = CastVideoFilterType::New();
  RescaleImageFilterType::Pointer imageRescaler = RescaleImageFilterType::New();
  RescaleVideoFilterType::Pointer videoRescaler = RescaleVideoFilterType::New();
  FrameAverageFilterType::Pointer frameAverageFilter = FrameAverageFilterType::New();

  // Set up the reader and writer
  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );

  // Set up the frame average filter
  frameAverageFilter->SetNumberOfFrames(6);

  // Set up the caster and rescaler
  videoCaster->SetImageFilter( imageCaster );
  videoRescaler->SetImageFilter( imageRescaler );

  // Set up the video filter
  imageFilter->SetVariance( 0.5 );
  imageFilter->SetMaximumError(.01f);
  imageFilter->SetLowerThreshold( 10 );
  imageFilter->SetUpperThreshold( 25 );
  videoFilter->SetImageFilter( imageFilter );

  // Connect the pipeline
  frameAverageFilter->SetInput( reader->GetOutput() );
  videoCaster->SetInput( frameAverageFilter->GetOutput() );
  videoFilter->SetInput( videoCaster->GetOutput() );
  videoRescaler->SetInput( videoFilter->GetOutput() );
  //writer->SetInput( videoRescaler->GetOutput() );

  writer->SetInput( frameAverageFilter->GetOutput() );

  //frameAverageFilter->SetInput( videoFilter->GetOutput() );
  //videoRescaler->SetInput( frameAverageFilter->GetOutput() );

  //DEBUG
  //IOVideoType::BufferType* buff = reader->GetOutput()->GetFrameBuffer();
  //buff->SetNumberOfBuffers(6);
  //reader->GetOutput()->SetFrameBuffer(buff);
  //frameAverageFilter->UpdateOutputInformation();
  //std::cout << "Num Buffers: " << frameAverageFilter->GetOutput()->GetNumberOfBuffers() << std::endl;

  // Call Update to execute the pipeline
  //frameAverageFilter->Update();
  writer->Update();

  //DEBUG
  std::cout << "Num Buffers: " << reader->GetOutput()->GetNumberOfBuffers() << std::endl;
  std::cout << "Requested temp region duration: " << reader->GetOutput()->GetRequestedTemporalRegion().GetFrameDuration() << std::endl;

  return 0;
}

