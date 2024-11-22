#include "motionDiff.h"

motionDiff::motionDiff(){
    video.open(pipeline, CAP_GSTREAMER);
    assert(video.isOpened());
    setFrame();
}

motionDiff::~motionDiff(){
    stopThread();
}

void motionDiff::setFrame(){
    //기준프레임 갱신
    if(!video.read(standard)){
        cout << "Frame capture Error\n";
        exit(1);
    }
    cout << "\033[34;47mFrame updated newly\033[0m\n";

    //연산 속도 향상 위한 이미지 처리
    cvtColor(standard, standard, COLOR_BGR2GRAY); //그레이스케일
    GaussianBlur(standard, standard, Size(5, 5), 1.0); //가우시안 블러로 노이즈 제거
}

void motionDiff::calcDiff(){
    //차영상 계산
    while(1){
        if(stop_thread.load())
            break;
        
        Mat local_standard;
        unique_lock<mutex> lock(mtx);
        conv.wait_for(lock, chrono::milliseconds(5)); //5ms마다 프레임 갱신 여부 확인
        local_standard = standard.clone();
        
        if(!video.read(frame)){
            cout << "Frame capture Error\n";
            exit(1);
        }
        //연산 속도 향상 위한 이미지 처리
        cvtColor(frame, grayscale, COLOR_BGR2GRAY);
        GaussianBlur(grayscale, grayscale, Size(5, 5), 1.0);

        absdiff(local_standard, grayscale, diff);
        //absdiff(standard, grayscale, diff);
        threshold(diff, diff, 50, 255, THRESH_BINARY);

        //너무 많은 감지가 되면? 카메라를 이동중이거나 뭔가 다른 문제가 생겼을 수도 있으니 그 부분을 감지하는것도 추가
        
        if(countNonZero(diff) > 500){ //변화 O
            cout << "\033[0;31mMotion Detected\033[0m\n";
            motionDetected.store(true);
            setFilename();
            imwrite(filename + ".png", frame);
        }
        else{
            motionDetected.store(false);
        }

        //프레임 갱신
        //standard = grayscale.clone();
    }
}

void motionDiff::setFilename(){
    //현재 시간으로 파일 이름 설정
    auto now = chrono::system_clock::now();
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_time_t);

    string year = to_string(now_tm->tm_year + 1900);
    string month = (now_tm->tm_mon + 1 < 10 ? "0" : "") + to_string(now_tm->tm_mon + 1);
    string day = (now_tm->tm_mday < 10 ? "0" : "") + to_string(now_tm->tm_mday);
    string hour = (now_tm->tm_hour < 10 ? "0" : "") + to_string(now_tm->tm_hour);
    string minute = (now_tm->tm_min < 10 ? "0" : "") + to_string(now_tm->tm_min);
    string second = (now_tm->tm_sec < 10 ? "0" : "") + to_string(now_tm->tm_sec);

    filename = year + month + day + "_" + hour + ":" + minute + ":" + second;
}

void motionDiff::noticeClient(){
    //소켓통신으로 클라이언트에게 물체 감지를 알림
    //한번만 가도록

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(1);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(TCP_PORT);
    if (bind(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind()");
        exit(1);
    }
    if (listen(ssock, 8) < 0) {
        perror("listen()");
        exit(1);
    }
    clen = sizeof(cliaddr);

    int csock = accept(ssock, (struct sockaddr *)&cliaddr, &clen);
    if (csock < 0) {
        perror("accept()");
        close(ssock); // 서버 소켓 닫기
        exit(1);
    }

    inet_ntop(AF_INET, &cliaddr.sin_addr, mesg, BUFSIZ);
    cout << "Client is connected : " << mesg << endl;

    while(1){
        if(stop_thread.load())
            break;
        if(motionDetected.load()){
            cout << "\033[31;47mNotice to client\033[0m\n";
            if (write(csock, toClient, strlen(toClient)) <= 0) {
                perror("write()");
                break;
            }
            motionDetected.store(false);
            this_thread::sleep_for(chrono::seconds(20));
        }
    }
}

void motionDiff::runPeriodically(){
    //일정 시간 지날때마다 프레임 갱신
    while(1){
        if(stop_thread.load())
            break;
        {
            unique_lock<mutex> lock(mtx);
            setFrame();
            conv.notify_one(); //calcDiff에게 갱신 알림
        }
        this_thread::sleep_for(chrono::seconds(100)); //100초에 한번 프레임 갱신
    }
}

void motionDiff::startThread(){
    //스레드 생성 및 시작
    detect = thread(&motionDiff::calcDiff, this);
    notice = thread(&motionDiff::noticeClient, this);
    frameset = thread(&motionDiff::runPeriodically, this);
}

void motionDiff::stopThread(){
    //스레드 종료
    stop_thread.store(true);
    conv.notify_all();
    detect.join();
    notice.join();
    frameset.join();
}