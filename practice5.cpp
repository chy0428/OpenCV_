#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat image = imread("images/Fig06_strawberry.tif");
    Mat HSV, mask_out;
    vector<Mat> mo(3);
    vector<Mat> ic(3);
    int rows = image.rows; 
    int cols = image.cols; 
    uchar* h;
    uchar* s;
    uchar* v;
    cvtColor(image, HSV, CV_BGR2HSV); 
    split(HSV, mo);

    //eqaulizing the histogram of I mat 
    equalizeHist(ic[2], ic[2]);
    
    //masking out except strawberry
    for (int j = 0; j < rows; j++) {
        h = mo[0].ptr<uchar>(j);
        s = mo[1].ptr<uchar>(j);
        for (int i = 0; i < cols; i++) {
            if (h[i] > 159 && h[i] < 180) s[i] = s[i];
            else s[i] = 0; 
        }
    }

    merge(mo, mask_out);
    cvtColor(mask_out, mask_out, CV_HSV2BGR); 
    imshow("image", image); 
    imshow("mask out", mask_out); 

    waitKey(0);
}

   