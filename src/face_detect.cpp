#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void detect_and_display (Mat frame);
void highlight_face (Mat frame, Rect face);
void highlight_eye (Mat frame, Rect face, Rect eye);

String face_cascade_name = "res/classifiers/lbpcascade_frontalface.xml";
String eyes_cascade_name = "res/classifiers/haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

int main (void) {
    VideoCapture capture;
    Mat frame;

    if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };
    if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading eyes cascade\n"); return -1; };

    capture.open(-1);

    if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

    while (capture.read(frame)) {
        if (frame.empty()) { printf(" --(!) No captured frame -- Break!"); break; }
        detect_and_display (frame);
        int c = waitKey(10);
        if ((char)c == 27) break;
    }

    return 0;
}

void detect_and_display (Mat frame) {
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor (frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist (frame_gray, frame_gray);

    face_cascade.detectMultiScale (frame_gray, faces, 1.1, 2, 0, Size(80, 80));

    for (size_t i = 0; i < faces.size(); i++) {

        Rect face = faces[i];
        Mat faceROI = frame_gray (face);
        std::vector<Rect> eyes;

        eyes_cascade.detectMultiScale (faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30));
        
        if (eyes.size() == 2) {
            highlight_face (frame, face);
            for (size_t j = 0; j < eyes.size(); j++) highlight_eye (frame, face, eyes[j]);
        }

    }

    imshow ("face_detect", frame);
}

void highlight_face (Mat frame, Rect face) {
    Point center (face.x + face.width / 2, face.y + face.height / 2);
    ellipse (frame, center, Size (face.width / 2, face.height / 2), 0, 0, 360, Scalar (255, 0, 0), 10, 8, 0);
}

void highlight_eye (Mat frame, Rect face, Rect eye) {
    Point eye_center (face.x + eye.x + eye.width / 2, face.y + eye.y + eye.height / 2);
    int radius = cvRound ((eye.width + eye.height) * 0.25);
    circle (frame, eye_center, radius, Scalar( 255, 0, 255 ), 5, 8, 0);
}