#include "motionDiff.h"
#include "camera_server.h"

motionDiff::motionDiff(mutex& mtx)
    : mtx(mtx){}

motionDiff::~motionDiff(){

}

void motionDiff::frameUpdate(Mat mainframe){
    frame = mainframe;
}

void motionDiff::setFrame(){
    unique_lock<mutex> lock(mtx);
    conv.wait(lock, [&]{ return this->frameReady; });

    if(standard.empty()){
        cout << "standard frame is empty\n";
        exit(1);
    }

    cout << "\033[34;47mFrame updated\033[0m\n";

    //연산 속도 향상 위한 이미지 처리
    cvtColor(standard, standard, COLOR_BGR2GRAY); //그레이스케일
    GaussianBlur(standard, standard, Size(5, 5), 1.0); //가우시안 블러로 노이즈 제거
}

int motionDiff::calcDiff(){
    //차영상 계산   
    unique_lock<mutex> lock(mtx);
    conv.wait(lock, [&]{ return this->frameReady; });

    if(frame.empty()){
        cout << "frame is empty\n";
        exit(1);
    }

    //연산 속도 향상 위한 이미지 처리
    cvtColor(frame, grayscale, COLOR_BGR2GRAY);
    GaussianBlur(grayscale, grayscale, Size(5, 5), 1.0);

    absdiff(standard, grayscale, diff);
    threshold(diff, diff, 50, 255, THRESH_BINARY);
    
    if(countNonZero(diff) > 100){ //변화 O
        //cout << "\033[0;31mMotion Detected\033[0m\n";
        // setFilename();
        // imwrite(filename + ".png", frame);

        standard = grayscale.clone();
        frameReady = false;
        return 1;
    }
    else{
        standard = grayscale.clone();
        frameReady = false;
        return 0;
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