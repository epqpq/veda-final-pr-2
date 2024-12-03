#ifndef _CAMERA_SERVER_H_
#define _CAMERA_SERVER_H_

#include <opencv4/opencv2/opencv.hpp>
#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <string>
#include <iostream>
#include <thread>
#include <cstring>
#include <sstream>
#include <vector>
#include <chrono>
#include <atomic>

#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace std;
using namespace chrono;

#define TCP_PORT 5100

class cServer
{
private:
    std::string pipelineStr;
    cv::VideoCapture cap;
    cv::VideoWriter videoWriter;
    std::string getIp();
    vector<string> flagv;
    istringstream ss;
    string temp;
    string videoName;

    time_point<steady_clock> now_t;
    time_point<steady_clock> motion_t = steady_clock::time_point::min(); //최소시간으로 초기화
    time_point<steady_clock> fire_t = steady_clock::time_point::min();

    //for tcp
    int ssock, csock, readstr;
    socklen_t clen;
    struct sockaddr_in servaddr, cliaddr;
    char cIP[BUFSIZ];
    char mesg[BUFSIZ];
    const char* noticeMotion = "1;motion";
    const char* noticeFire = "1;fire";
public:
    GstElement* pipeline = nullptr;
    atomic<int> tcpFlag = 0; //통신을 위한 플래그
    atomic<bool> power_motion = true;
    atomic<bool> power_fire = true;  //기능 on/off를 위한 플래그
    thread tcpThread;
    cServer();
    ~cServer();
    int init();
    cv::Mat getSource();
    int setSource(cv::Mat);
    void tcpCommunication();
};

#endif