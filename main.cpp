#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main(int argc, char** argv) {
	//VideoCapture capture;
	//capture.open("./bike.avi");
	VideoCapture capture_0(0);
	VideoCapture capture_1(1);
	VideoCapture capture_2(2);
	//capture.set(CV_CAP_PROP_FRAME_WIDTH , 640);
	//capture.set(CV_CAP_PROP_FRAME_HEIGHT ,480);
	if (!(capture_0.isOpened()&capture_1.isOpened() & capture_2.isOpened()))
	{
		printf("[%s][%d]could not load video data...\n", __FUNCTION__, __LINE__);
		return -1;
	}

	Mat frame, frame1, frame2;
	while (capture_0.read(frame)& capture_1.read(frame1)& capture_2.read(frame2))
	{
		imshow("video-0", frame);
		imshow("video-1", frame1);
		imshow("video-2", frame2);
		char c = waitKey(66);
		if (c == 27)
		{
			break;
		}
	}
	waitKey(0);
	return 0;

}