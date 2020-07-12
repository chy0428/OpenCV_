#include <iostream>
#include "cv.hpp"

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("images/Fig06_chalk.tif", 1);
    resize(img, img, Size(0, 0), 0.5, 0.5);

    uchar gamma_table[256]; 
    //get_gamma_LUT(gamma_table,2.5);
    for (int i = 0; i < 256; i++) {
        gamma_table[i] = pow((i / 255.f), 2.5) * 255.0f;
    }
    Mat gamma_mat(1, 256, CV_8UC1, gamma_table);
    vector<Mat> channels; split(img, channels);

    for (int i = 0; i < 3; i++) {
        LUT(channels[i], gamma_mat, channels[i]); 
    }
    Mat res;
    merge(channels,res);
    imshow("Original img", img); 
    imshow("Rsult img", res); 
    waitKey(0);
}



   