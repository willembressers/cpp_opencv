#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	// instantiate the camera capture
	VideoCapture capture;

	// define a frame variables
	Mat frame;
	Mat gray;

	// define vector variable
	std::vector<Rect> faces;

	// PreDefined trained XML classifiers with facial features 
	CascadeClassifier cascade;
  
	// Load face cascade classifier
	if( !cascade.load( "data/haarcascades/haarcascade_frontalface_default.xml" ) )
	{
		cout << "--(!)Error loading face cascade\n";
		return -1;
	};

	// check if the camera could be opened
	if(!capture.open(0))
	{
		cout << "--(!)Error opening video capture\n";
		return 0;
	}

	// capture frame-by-frame
	while ( capture.read(frame) )
	{

		// break the loop if the frame is empty
		if( frame.empty() ) 
		{
			cout << "--(!) No captured frame -- Break!\n";
			break;
		}

		// convert to grayscale
		cvtColor( frame, gray, COLOR_BGR2GRAY );

		// improve contrast (by histogram equalization)
		equalizeHist( gray, gray );

		// detect faces
		cascade.detectMultiScale( gray, faces );

		// loop over the faces
		for ( size_t i = 0; i < faces.size(); i++ )
		{
			// draw rectangle
			cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0), 3);
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