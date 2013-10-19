#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(void) {
    Mat image(cvLoadImage("res/images/pnid.jpg", 1));
    imshow("show_image", image);
    waitKey(0);
    return 0;
}