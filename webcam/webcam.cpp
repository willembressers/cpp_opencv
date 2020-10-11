#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char** argv)
{
	// instantiate the camera capture
	VideoCapture capture;

	// define a frame variable
	Mat frame;

	// check if the camera could be opened
	if(!capture.open(0))
	{
		// if not, end the function
		return 0;
	}

	// capture frame-by-frame
	while ( capture.read(frame) )
	{
		// break the loop if the frame is empty
		if( frame.empty() ) 
		{
			break;
		}

		// show the frame
		imshow("this is you, smile! :)", frame);

		 // stop capturing by pressing ESC 
		if( waitKey(10) == 27 ) 
		{
			break;
		}
	}

	// end the function
	return 0;
}