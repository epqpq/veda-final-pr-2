#ifndef _CAMERA_SERVER_H_
#define _CAMERA_SERVER_H_

#include <opencv4/opencv2/opencv.hpp>
#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <string>
#include <iostream>

#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class cServer
{
private:
    std::string pipeline;
    cv::VideoCapture cap;
    cv::VideoWriter videoWriter;
    
    std::string getIp();
public:
    cServer();
    ~cServer();
    int init();
    cv::Mat getSource();
    int setSource(cv::Mat);
};

#endif