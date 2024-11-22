#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <sys/time.h>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring> //memset, strcpy

using namespace cv;
using namespace std;

#define TCP_PORT 5100

class motionDiff {
    VideoCapture video;
    Mat standard, grayscale, diff;
    string pipeline = "libcamerasrc ! video/x-raw,width=640,height=480,framerate=10/1,format=RGBx ! videoconvert ! appsink";
    // 640x480 [58.92 fps - (16, 0)/2560x1920 crop]
    // 1296x972 [43.25 fps - (0, 0)/2592x1944 crop]
    // 1920x1080 [30.62 fps - (348, 434)/1928x1080 crop]
    // 2592x1944 [15.63 fps - (0, 0)/2592x1944 crop]
    string filename;
    thread detect, notice, frameset;
    //mutex mtx;
    condition_variable conv;
    atomic<bool> motionDetected = false;
    atomic<bool> stop_thread = false;  //기능 off시 true --> 스레드 종료
    int ssock;
    socklen_t clen;
    struct sockaddr_in servaddr, cliaddr;
    char mesg[BUFSIZ];
    const char* toClient = "Motion Detected  --from rpi";

public:
    Mat frame;
    mutex mtx;
    motionDiff();
    ~motionDiff();
    void setFrame();
    void calcDiff();
    void setFilename();
    void noticeClient();
    void runPeriodically();
    void startThread();
    void stopThread();
};