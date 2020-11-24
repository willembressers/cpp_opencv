#include "opencv2/opencv.hpp"
#include <sys/time.h>

using namespace std;
using namespace cv;

// ============================================================================
// Declare functions
// ============================================================================
int diff_ms(timeval t1, timeval t2);
void putFps(Mat &frame, timeval start);
void putDate(Mat &frame);
void detectAndDraw(Mat &img, CascadeClassifier &cascade);

// ============================================================================
// Main code
// ============================================================================
int main(int argc, char const *argv[])
{
	// declare variables
	Mat frame;
	VideoCapture capture;
	CascadeClassifier cascade;
	timeval start;

	// Load face cascade classifier
	if (!cascade.load("data/haarcascade_frontalface_default.xml"))
	{
		cout << "--(!)Error loading face cascade\n";
		return -1;
	};

	// check if the camera could be opened
	if (!capture.open(0))
	{
		cout << "--(!)Error opening video capture\n";
		return 0;
	}

	// capture frame-by-frame
	while (capture.read(frame))
	{
		// Get the current timestamp
		gettimeofday(&start, NULL);

		// break the loop if the frame is empty
		if (frame.empty())
		{
			cout << "--(!) No captured frame -- Break!\n";
			break;
		}

		// detect and draw faces in the frame
		detectAndDraw(frame, cascade);

		// add some metrics on the frame
		putFps(frame, start);
		putDate(frame);

		// show the frame
		imshow("this is you, smile! :)", frame);

		// stop capturing by pressing ESC
		if (waitKey(10) == 27)
		{
			break;
		}
	}

	// end the function
	return 0;
}

int diff_ms(timeval t1, timeval t2)
{
	return (((t1.tv_sec - t2.tv_sec) * 1000000) +
			(t1.tv_usec - t2.tv_usec)) /
		   1000;
}

void putFps(Mat &frame, timeval start)
{
	// declare variables
	timeval end;
	double fps;
	string text;

	// Get the current timestamp
	gettimeofday(&end, NULL);

	// calculat the frames per second
	fps = (1 / float(diff_ms(end, start))) * 1000;

	// construct the text
	text = format("fps: %.2f", fps);

	// add it to the frame
	putText(frame, text, Point(0, 30), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 255, 0));
}

void putDate(Mat &frame)
{
	// declare variables
	string text;
	char buffer[80];

	// current date/time based on current system
	time_t now = time(0);

	tm *ltm = localtime(&now);

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",ltm);

	// construct the text
	text = format("date: %s", buffer);

	// add it to the frame
	putText(frame, text, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 255, 0));
}

void detectAndDraw(Mat &frame, CascadeClassifier &cascade)
{
	// declare variables
	Mat gray;
	std::vector<Rect> faces;

	// convert to grayscale
	cvtColor(frame, gray, COLOR_BGR2GRAY);

	// improve contrast (by histogram equalization)
	equalizeHist(gray, gray);

	// detect faces
	cascade.detectMultiScale(gray, faces);

	// loop over the faces
	for (size_t i = 0; i < faces.size(); i++)
	{
		// draw rectangle
		cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0), 3);
	}
}