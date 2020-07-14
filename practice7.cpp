#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;
int main() {
    Mat img, blurred, dst, mask;
	img = imread("images/word_thresh.png");
    resize(img, img, Size(0,0), 0.5, 0.5);
	if (img.empty())
		return -1;
	imshow("org", img);

	mask = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	dilate(img, dst, mask);
	imshow("Dilate", dst);
	erode(img, dst, mask);
	imshow("erode", dst);
	morphologyEx(img, dst, MORPH_OPEN, mask, Point(-1, -1), 2);
	imshow("open", dst);
	morphologyEx(img, dst, MORPH_CLOSE, mask, Point(-1, -1), 2);
	imshow("close", dst);
    waitKey(0);
    
}
