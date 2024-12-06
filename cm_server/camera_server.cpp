#include "camera_server.h"

cServer::cServer()
{
    auto now = system_clock::now();
    time_t now_time_t = system_clock::to_time_t(now);
    now_tm = localtime(&now_time_t);
    com_t = now_tm->tm_hour;
    com_m = now_tm->tm_min;
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
    
    auto now = chrono::system_clock::now();
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_time_t);
    string year = to_string(now_tm->tm_year + 1900);
    string month = (now_tm->tm_mon + 1 < 10 ? "0" : "") + to_string(now_tm->tm_mon + 1);
    string day = (now_tm->tm_mday < 10 ? "0" : "") + to_string(now_tm->tm_mday);
    videoName = year + month + day + ".mp4";

    pipelineStr = "libcamerasrc ! video/x-raw,width=640,height=480,format=RGBx ! videoconvert ! appsink";

    pipeline = gst_parse_launch(pipelineStr.c_str(), nullptr);
    if (!pipeline) {
        std::cerr << "Error: Failed to create pipeline.\n";
        return -1;
    }
    cap.open(pipelineStr, cv::CAP_GSTREAMER);
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

    // TCP 통신 소켓 오픈
    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(1);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(TCP_PORT);
    int on = 1;
    if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("setsockopt()");
        return -1;
    }
    if (bind(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind()");
        exit(1);
    }
    if (listen(ssock, 8) < 0) {
        perror("listen()");
        exit(1);
    }
    clen = sizeof(cliaddr);

    //클라이언트가 접속할 때까지 대기
    cout << "Waiting client . . ."<<endl;
    csock = accept(ssock, (struct sockaddr *)&cliaddr, &clen);
    if (csock < 0) {
        perror("accept()");
        close(ssock); // 서버 소켓 닫기
        exit(1);
    }

    inet_ntop(AF_INET, &cliaddr.sin_addr, cIP, BUFSIZ);
    cout << "Client is connected : " << cIP << endl;

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

void cServer::tcpCommunication(){
    //tcp 통신

    int flags = fcntl(csock, F_GETFL, 0);
    fcntl(csock, F_SETFL, flags | O_NONBLOCK);

    while(1){
        now_t = steady_clock::now();
        //send
        //motion_t, fire_t가 초기시간이거나(the first send), 20초가 지났을 때만 전송할 수 있도록 함
        if(tcpFlag.load() == 1 &&
                (motion_t == steady_clock::time_point::min() || duration_cast<seconds>(now_t - motion_t).count() >= 20)){ //motion 알림
            motion_t = steady_clock::now();
            cout << "\033[31;47mNotice to client \033[0m\n";
            if (write(csock, noticeMotion, strlen(noticeMotion)) <= 0) {
                perror("write()");
                break;
            }
            tcpFlag.store(0);
        }
        if(tcpFlag.load() == 2 &&
                (fire_t == steady_clock::time_point::min() || duration_cast<seconds>(now_t - fire_t).count() >= 20)){ //fire 알림
            fire_t = steady_clock::now();
            cout << "\033[31;47mNotice to client\033[0m\n";
            if (write(csock, noticeFire, strlen(noticeFire)) <= 0) {
                perror("write()");
                break;
            }
            tcpFlag.store(0);
        }

        //recv
        try{
            readstr = read(csock, mesg, BUFSIZ);

            if(readstr > 0){ //클라이언트로부터 메시지 도착
                mesg[readstr] = '\0';
                //ex)  2;fire;on     -> 문자열 분할
                ss.str(mesg);
                ss.clear();

                flagv.clear();
                while(getline(ss, temp, ';'))
                    flagv.push_back(temp);

                if(flagv[0] == "2"){
                    if(flagv[1] == "motion"){
                        if(flagv[2] == "on"){
                            power_motion.store(true);
                            cout<<"motion on --from client\n";
                        }
                        else{
                            power_motion.store(false);
                            cout<<"motion off --from client\n";
                        }
                    }
                    else if(flagv[1] == "fire"){
                        if(flagv[2] == "on"){
                            power_fire.store(true);
                            cout<<"fire on --from client\n";
                        }
                            
                        else{
                            power_fire.store(false);
                            cout<<"fire off --from client\n";
                        }
                    }
                }
                else{ //정상적인 recv x
                    cout << "Invalid message received.\n";
                }
            }
            else if(readstr == 0){ //클라이언트가 연결 끊음
                cout << "Client disconnected" << endl;
                break;
            }
            else if(errno == EAGAIN || errno == EWOULDBLOCK){
                //데이터 없으면 루프 재시작
                this_thread::sleep_for(milliseconds(10)); //cpu 과부하 방지
                continue;
            }
            else{
                throw system_error(errno, generic_category(), "Error during read()");
            }
        }
        catch(const system_error& e){
            cerr << e.what() << endl;
                break;
        }
    }
    close(csock);
    close(ssock);
}
void cServer::record(const cv::Mat& frame){
    auto now = system_clock::now();
    time_t now_time_t = system_clock::to_time_t(now);
    now_tm = localtime(&now_time_t);

    int now_t = now_tm->tm_hour;
    int now_m = now_tm->tm_min;
    
    if(!bRec) {
        videoName = setVideoname();
        recordWriter.open(videoName, cv::VideoWriter::fourcc('H','2','6','4'), 30.0, cv::Size(640, 480), true);
        bRec = true;
    }
    if(now_m != com_m){
        com_m = now_m;
        recordWriter.release();
        videoName = setVideoname();
        recordWriter.open(videoName, cv::VideoWriter::fourcc('H','2','6','4'), 30.0, cv::Size(640, 480), true);
    }
    recordWriter.write(frame);
}
string cServer::setVideoname(){
    string year = to_string(now_tm->tm_year + 1900);
    string month = (now_tm->tm_mon + 1 < 10 ? "0" : "") + to_string(now_tm->tm_mon + 1);
    string day = (now_tm->tm_mday < 10 ? "0" : "") + to_string(now_tm->tm_mday);
    string hour = (now_tm->tm_hour < 10 ? "0" : "") + to_string(now_tm->tm_hour);
    string minute = (now_tm->tm_min < 10 ? "0" : "") + to_string(now_tm->tm_min);
    
    string filename = year + month + day + "_" + hour + minute +".mp4";
    return filename;
}