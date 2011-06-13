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

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>


// Process a single frame of video and return the resulting frame
cv::Mat processFrame( const cv::Mat& inputImage )
{
  // No processing yet
  // ADD FRAME PROCESSING CODE HERE
  return inputImage;
}


// Iterate through a video, process each frame, and display the result in a GUI.
void processAndDisplayVideo(cv::VideoCapture& vidCap)
{
  // get the video frame rate, width, and height
  double frameRate = vidCap.get( CV_CAP_PROP_FPS );
  int width = vidCap.get( CV_CAP_PROP_FRAME_WIDTH );
  int height = vidCap.get( CV_CAP_PROP_FRAME_HEIGHT );

  // The title string for the GUI window
  std::string windowName = "Exercise 1: Basic Filtering in OpenCV";
  // create a window, CV_WINDOW_FREERATIO is needed for display with OpenGL
  cv::namedWindow( windowName, CV_WINDOW_FREERATIO);
  // resize the window to match the size of the video
  cvResizeWindow( windowName.c_str(), width, height );

  // compute the number of millisecond to delay between drawing frames
  unsigned delay = 1000 / frameRate;

  // create a matrix object to store the current video frame
  cv::Mat frame;
  // loop until no more frames can be read from the video capture object
  while( vidCap.read(frame) )
  {
    // apply some processing to the frame (see function above)
    cv::Mat outputFrame = processFrame( frame );
    // show the image in the previously created window
    cv::imshow( windowName, outputFrame );

    // wait for the user to press a key or for the time delay to pass
    if( cv::waitKey(delay) >= 0 )
    {
      break;
    }
  }
}


// Iterate through a video, process each frame, and save the processed video.
void processAndSaveVideo(cv::VideoCapture& vidCap, const std::string& filename)
{
  // get the video frame rate, width, and height
  double frameRate = vidCap.get( CV_CAP_PROP_FPS );
  int width = vidCap.get( CV_CAP_PROP_FRAME_WIDTH );
  int height = vidCap.get( CV_CAP_PROP_FRAME_HEIGHT );

  // Specify that the output video will be encoded in DIVX format
  int fourcc = CV_FOURCC('D','I','V','X');
  // Create a video writer object with the specified
  CvVideoWriter* vidWrite = cvCreateVideoWriter( filename.c_str(),
                                                 fourcc, frameRate,
                                                 cvSize(width, height) );

  // create a matrix object to store the current video frame
  cv::Mat frame;
  // loop until no more frames can be read from the video capture object
  while( vidCap.read(frame) )
  {
    // apply some processing to the frame (see function above)
    cv::Mat outputFrame = processFrame( frame );
    // convert to the old IplImage format (required for cvWriteFrame)
    IplImage outputFrameIpl = IplImage(outputFrame);
    // write the resulting image to the output video file
    cvWriteFrame( vidWrite, &outputFrameIpl );
  }

  // close the video file and release the memory for the writer
  cvReleaseVideoWriter( &vidWrite );
}


int main ( int argc, char **argv )
{
  // if there are no arguments then print usage and exit
  // Note: argv[0] is always set to the executable name
  if( argc < 2 )
  {
    std::cout << "Usage: "<< argv[0] <<" input_image output_image"<<std::endl;
    return -1;
  }

  // open the input video from the specified file
  cv::VideoCapture vidCap( argv[1] );
  // if video is not opened, report an error an exit
  if( !vidCap.isOpened() )
  {
    std::cerr << "Unable to open video file: "<< argv[1] << std::endl;
    return -1;
  }

  // if there is only an input file specified then display the result on screen
  if(argc < 3)
  {
    processAndDisplayVideo( vidCap );
  }
  // otherwise, write the resulting video to the specified output file.
  else
  {
    processAndSaveVideo( vidCap, argv[2] );
  }

  return 0;
}

