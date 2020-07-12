#include <iostream>
#include "cv.hpp"

using namespace std;
using namespace cv;

int main() {
	Mat img, blurred, dst, mask;
	img = imread("images/Fig09_mask.tif");
	imshow("org", img);

	mask = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	dilate(img, dst, mask);
	imshow("Dilate", dst);
	erode(img, dst, mask);
	imshow("erode", dst);

	morphologyEx(img, dst, MORPH_OPEN, mask, Point(-1, -1), 1);
	imshow("open", dst);
	morphologyEx(img, dst, MORPH_CLOSE, mask, Point(-1, -1), 1);
	imshow("close", dst);

	waitKey(0);
}
