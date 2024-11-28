#ifndef _MOTIONDIFF_H_
#define _MOTIONDIFF_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <sys/time.h>
#include <mutex>
#include <chrono>
#include <atomic>
#include <condition_variable>

#include "camera_server.h"

using namespace cv;
using namespace std;

#define TCP_PORT 5100
extern condition_variable conv;
extern bool frameReady;
extern bool firstFrame;

class motionDiff {
    Mat frame, grayscale, diff;
    string filename;
    mutex& mtx;

public:
    Mat standard;
    motionDiff() = delete; //참조 멤버 초기화하지 않는 기본 생성자 삭제
    motionDiff(mutex& mtx);
    ~motionDiff();
    void frameUpdate(Mat mainframe);
    void setFrame();
    int calcDiff();
    void setFilename();
};

#endif