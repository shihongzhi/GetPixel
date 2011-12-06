#include "cv.h"
#include "highgui.h"
#pragma comment(lib,"opencv_core231.lib")
#pragma comment(lib,"opencv_highgui231.lib")
using namespace cv;

void mouseHandler(int event, int x, int y, int flags, void* param)
{
	IplImage* img0, * img1;
	CvFont    font;
	uchar*    ptr;
	char      label[20];

	img0 = (IplImage*) param;
	img1 = cvCloneImage(img0);

	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, .8, .8, 0, 1, 8);

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		/* read pixel */
		ptr = cvPtr2D(img1, y, x, NULL);

		/*
		* display the BGR value
		*/
		sprintf(label, "(%d, %d, %d)", ptr[0], ptr[1], ptr[2]);

		cvRectangle(
			img1,
			cvPoint(x, y - 12),
			cvPoint(x + 100, y + 4),
			CV_RGB(255, 0, 0),
			CV_FILLED,
			8, 0
			);

		cvPutText(
			img1,
			label,
			cvPoint(x, y),
			&font,
			CV_RGB(255, 255, 0)
			);

		cvShowImage("img", img1);
	}
}

int main(int argc, char** argv)
{
	IplImage* img;

	/* load image */
	img = cvLoadImage("d://20.jpg", 1);

	/* always check */
	assert(img);

	/* create a window and install mouse handler */
	cvNamedWindow("img", 1);
	cvSetMouseCallback("img", mouseHandler, (void*)img);

	cvShowImage("img", img);

	cvWaitKey(0);

	/* be tidy */
	cvDestroyAllWindows();
	cvReleaseImage(&img);

	return 0;
}