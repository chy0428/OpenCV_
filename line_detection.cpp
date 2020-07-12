#include <iostream>
#include "cv.hpp"
using namespace std;
using namespace cv;

int main() {
    Mat img = imread("images/Tangram/bird.png", IMREAD_COLOR);

	if (img.empty()) {
		cout << "Cannot read image" << endl;
		waitKey(0);
		return;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat edge;
	GaussianBlur(gray, gray, Size(3, 3), 2);
	Canny(gray, edge, 60, 150, 3);
	imshow("edges", edge);
	
    //Hough Transform
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180.0, 100, 30, 10);

	//draw lines
	for (size_t i = 0; i < lines.size(); i++) {
		line(img, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 0, 200), 2);
	}

	imshow("Lines", img);
	imshow("Original", gray);
	
    waitKey(0);
	destroyAllWindows();
}
