#ifndef _FIRE_DETECTOR_H
#define _FIRE_DETECTOR_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <opencv2/core/ocl.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/model.h"
#include <cmath>

using namespace cv;
using namespace std;

class FireDetector{
private:
    Mat image;
    std::unique_ptr<tflite::Interpreter> interpreter;
public:
    FireDetector();
    FireDetector(const char*);
    bool detect_from_video(Mat&);

};


#endif