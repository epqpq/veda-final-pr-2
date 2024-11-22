#include "camera_server.h"

cServer::cServer()
{

}

cServer::~cServer()
{
    cap.release();
    cv::destroyAllWindows();
    videoWriter.release();
}

int cServer::init()
{
    gst_init(nullptr, nullptr);
    pipeline = "libcamerasrc ! video/x-raw,width=640,height=480,format=RGBx ! videoconvert ! appsink";
    cap.open(pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open the camera with GStreamer pipeline.\n";
        return -1;
    }

    // GStreamer TCP 서버를 위한 파이프라인
    std::string gst_pipeline = "appsrc ! videoconvert ! x264enc tune=zerolatency bitrate=3000 speed-preset=ultrafast ! mpegtsmux ! tcpserversink host=0.0.0.0 port=5000";

    // VideoWriter를 사용해 파이프라인 초기화
    videoWriter.open(gst_pipeline, cv::CAP_GSTREAMER, 0, 30, cv::Size(640, 480), true);
    if (!videoWriter.isOpened()) {
        std::cerr << "Failed to open GStreamer pipeline.\n";
        return -1;
    }

    return 0;
}

cv::Mat cServer::getSource()
{
    cv::Mat frame;
    if (!cap.read(frame)) {
        std::cerr << "Error: Unable to grab frame from camera.\n";
        return cv::Mat();
    }

    return frame;
}

int cServer::setSource(cv::Mat frame)
{
    // GStreamer로 프레임 전달
    if (!frame.empty()) {
        videoWriter.write(frame);
    } else {
        return -1;
    }

    return 0;
}

std::string cServer::getIp()
{
    struct ifaddrs *ifap = nullptr;
    struct ifaddrs *i = nullptr;
    void *src;
    std::string ip_address = "";

    if(getifaddrs(&ifap)==0){ //creates a linked list of structures describing the network interfaces of the local system
        for(i = ifap; i != nullptr; i=i->ifa_next){
            if(i->ifa_addr == nullptr)
                continue;
            
            if(i->ifa_addr->sa_family == AF_INET){
                char tmp[INET_ADDRSTRLEN];
                src = &((struct sockaddr_in *)i->ifa_addr)->sin_addr;
                inet_ntop(AF_INET, src, tmp, INET_ADDRSTRLEN); // converts the network address structure to character string
                if(strcmp(i->ifa_name, "lo")!=0){ // 127.0.0.1 제외
                    ip_address = tmp;
                    break;
                }
            }
        }
    }

    if (ifap != nullptr) {
        freeifaddrs(ifap);
    }

    return ip_address;
}