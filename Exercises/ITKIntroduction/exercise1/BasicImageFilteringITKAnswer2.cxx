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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCastImageFilter.h"
#include "itkCannyEdgeDetectionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main( int argc, char * argv [] )
{
  if( argc < 6 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImageFile outputImageFile variance lowerThreshold upperThreshold" << std::endl;
    return EXIT_FAILURE;
    }

  typedef   unsigned char  InputPixelType;
  typedef   float          RealPixelType;
  typedef   unsigned char  OutputPixelType;

  typedef itk::Image< InputPixelType,  2 >   InputImageType;
  typedef itk::Image< OutputPixelType, 2 >   OutputImageType;
  typedef itk::Image< RealPixelType,   2 >   RealImageType;

  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );


  typedef itk::CastImageFilter<
    InputImageType, RealImageType >  CastFilterType;

  CastFilterType::Pointer caster = CastFilterType::New();


  typedef itk::CannyEdgeDetectionImageFilter<
    RealImageType, RealImageType >  FilterType;

  FilterType::Pointer canny = FilterType::New();


  typedef itk::RescaleIntensityImageFilter<
    RealImageType, OutputImageType >  RescaleFilterType;

  RescaleFilterType::Pointer rescaler = RescaleFilterType::New();


  caster->SetInput( reader->GetOutput() );
  canny->SetInput( caster->GetOutput() );
  rescaler->SetInput( canny->GetOutput() );
  writer->SetInput( rescaler->GetOutput() );


  canny->SetVariance( atof( argv[3] ) );
  canny->SetLowerThreshold( atof( argv[4] ) );
  canny->SetUpperThreshold( atof( argv[5] ) );


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
