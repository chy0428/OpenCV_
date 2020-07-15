#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace std;
using namespace cv;

int checkPoly(vector<Point>& poly, float margin);
double getDistance(const Point& p1, const Point& p2);

int main () {
    int count = 0;
	Mat src = imread("images/bird.png");
	if (src.empty()) {
        printf("File read error!\n");
        exit(-1);
    }

	Mat canny;
	Canny(src, canny, 30, 60);
	dilate(canny, canny, Mat(), Point(-1, -1), 1);
	imshow("Canny", canny);

	//find contours
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//	findContours(canny.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	findContours(canny.clone(), contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	if (contours.size() <= 0) {
		cout << "No components" << endl;
		return -1;
	}

	int triangle = 0, srect = 0, prect = 0;
	Mat result = src.clone();

	for (size_t i = 0; i < contours.size(); i++) {
		vector<Point> poly;
		approxPolyDP(contours[i], poly, 10, true);
		int ret = 0;
		ret = checkPoly(poly, 0.7);

		if (ret != -1) {
			count++;
			polylines(result, poly, true, Scalar(0, 0, 0), 2);
			RotatedRect minrect = minAreaRect(poly);

			if (minrect.size.width * minrect.size.height < 90)
				continue;
			if (ret == 3) {
				triangle++;
				putText(result, "T", minrect.center, FONT_HERSHEY_COMPLEX, 0.6, Scalar(0, 0, 0), 2);
			}
			else if (ret == 4) {
				srect++;
				putText(result, "SR", minrect.center, FONT_HERSHEY_COMPLEX, 0.6, Scalar(0, 0, 0), 2);
			}
			else if (ret == 5) {
				prect++;
				putText(result, "PR", minrect.center, FONT_HERSHEY_COMPLEX, 0.6, Scalar(0, 0, 0), 2);
			}
		}
	}

	cout << "The number of polygons: " << count << endl;
	cout << "Tri: " << triangle << " SR:" << srect << " PR:" << prect << endl;

	imshow("src", src);
	imshow("result", result);
	waitKey(0);
	destroyAllWindows();
}

double getDistance(const Point& p1, const Point& p2) {
	double distance;
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	return distance;
}

int checkPoly(vector<Point>& poly, float margin) {
	vector<float> lines;

	//calculate distances between vertices
	for (int i = 0; i < poly.size(); i++) {
		lines.push_back(getDistance(poly[i], poly[(i + 1) % poly.size()]));
	}
	sort(lines.begin(), lines.end());	//sort by ascending order

	vector<float>sideLenRatio;
	for (int i = 0; i < lines.size(); i++) {
		sideLenRatio.push_back(lines[i] / lines[0]);
	}

	if (lines.size() == 3) {
		if (((sideLenRatio[0] >= (1 - margin)) && (sideLenRatio[0] <= (1 + margin))) &&
			((sideLenRatio[1] >= (1 - margin)) && (sideLenRatio[1] <= (1 + margin))) &&
			((sideLenRatio[2] >= (1.4 - margin)) && (sideLenRatio[2] <= (1.4 + margin))))
			return 3; 
		else return -1;
	}

	else if (lines.size() == 4) {
		if (((sideLenRatio[0] >= (1 - margin)) && (sideLenRatio[0] <= (1 + margin))) &&
			((sideLenRatio[1] >= (1 - margin)) && (sideLenRatio[1] <= (1 + margin))) &&
			((sideLenRatio[2] >= (1 - margin)) && (sideLenRatio[2] <= (1 + margin))) &&
			((sideLenRatio[3] >= (1 - margin)) && (sideLenRatio[3] <= (1 + margin))))
			return 4;

        else if (((sideLenRatio[0] >= (1 - margin)) && (sideLenRatio[0] <= (1 + margin))) &&
            ((sideLenRatio[1] >= (1 - margin)) && (sideLenRatio[1] <= (1 + margin))) &&
            ((sideLenRatio[2] >= (1.4 - margin)) && (sideLenRatio[2] <= (1.4 + margin))) &&
            ((sideLenRatio[3] >= (1.4 - margin)) && (sideLenRatio[3] <= (1.4 + margin))))
            return 5; //����纯 - 1:1:1.4:1.4

        else
            return -1;
    }
	else return -1;
}
