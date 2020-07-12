#include <iostream>
#include "cv.hpp"

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("images/Fig06_lenna.tif", 1);
	Mat hsv, filtered, rgb_filtered;
	imshow("org", img);
	vector<Mat> rgb_ch(3);
    std::vector<Mat> channel(3);
	split(img, rgb_ch);

	for (int i = 0; i < 3; i++) {
		Laplacian(rgb_ch[i], filtered, CV_16S);
		convertScaleAbs(filtered, filtered);
		rgb_ch[i] = rgb_ch[i] + 1.5 * filtered;
	}
	merge(rgb_ch, rgb_filtered);
	imshow("Laplacian (RGB)", rgb_filtered);

	cvtColor(img, hsv, COLOR_BGR2HSV);
	split(hsv, channel);
	
	Laplacian(channel[2], filtered, CV_16S);
	convertScaleAbs(filtered, filtered);
	channel[2] = channel[2] + 1.5 * filtered;
	
	merge(channel, hsv);
	cvtColor(hsv, img, COLOR_HSV2BGR);
	imshow("Laplacian(HSV)", img);

	waitKey(0);
}

//   Mat image = imread("images/Fig06_lenna.tif", 1);
// 	Mat laplacian, abs_laplacian, sharpening; 
//     GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT); 
//     // calculates the Laplacian of an image
//     // image: src, laplacian: dst, CV_16S: desire depth of dst,
//     // 1: aperture size used to compute second-derivative (optional) 
//     // 1: optional scale factor for the computed Laplacian values
//     // 0: optional delta value that is added to the result 
//     Laplacian(image, laplacian, CV_16S, 1, 1, 0); 
//     convertScaleAbs(laplacian, abs_laplacian); 
//     sharpening = abs_laplacian + image;
//     imshow("Input image", image); 
//     imshow("Laplacian", laplacian); 
//     imshow("abs_Laplacian", abs_laplacian); 
//     imshow("Sharpening", sharpening);
//     waitKey(0);