#include "camera_server.h"
#include "motionDiff.h"
#include "fire_detector.h"

#include <wiringPi.h>
#include <softTone.h>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <iostream>
#include <atomic>
#define BUZZER_PIN 23
#define LED_PIN 18

using namespace cv;
using namespace std;

std::vector<std::string> Labels;
std::mutex mtx;
std::condition_variable conv;
std::atomic<bool> running(false); //사이렌 제어용 변수

void playSiren() {
    // int count = 0;
    // int duration_per_note = 500; // 각 음의 지속 시간(ms)

    // while(count < duration_ms){
    //     for (int i = 0; i < note_length; ++i) {
    //     softToneWrite(BUZZER_PIN, note[i]); // 현재 주파수 출력
    //     usleep(duration_per_note);  // 지속 시간 대기
    //     count += duration_per_note;
    //     }
    // }

    while(1){
        if(running){
            digitalWrite(LED_PIN, HIGH);
            softToneWrite(BUZZER_PIN, 1500);
        }else{
            digitalWrite(LED_PIN, LOW);
            softToneWrite(BUZZER_PIN, 0);
        }
        
        usleep(10);
    }

    // digitalWrite(LED_PIN, LOW);
    // softToneWrite(BUZZER_PIN, 0); // 사이렌 종료 후 소리 끔
}

void handleSignal(int signal) {
    if (signal == SIGINT) {
        std::cout << "\nSignal received. end the siren..." << std::endl;
        running = false; // running을 false로 설정하여 루프 종료
        digitalWrite(LED_PIN, LOW);
        softToneWrite(BUZZER_PIN, 0); // 사이렌 종료 후 소리 끔
    }
}

int main(int argc, char** argv)
{
    if (wiringPiSetupGpio() == -1) { // WiringPi 초기화
        std::cerr << "WiringPi setup failed!" << std::endl;
        return 1;
    }
    if (softToneCreate(BUZZER_PIN) != 0) { // 소프트톤 초기화
        std::cerr << "Failed to set up softTone on pin " << BUZZER_PIN << std::endl;
        return 1;
    }
    pinMode(LED_PIN, OUTPUT);
    std::signal(SIGINT, handleSignal);
    std::thread sirenThread(playSiren);
    sirenThread.detach();

    cServer mainSource;
    FireDetector fire_detector("firenet.tflite");

    int ret = mainSource.init();
    if (ret) {
        perror("Initialization failed\n");
        return 0;
    }

    cv::Mat frame;

    bool fireCheck = false;
    
    //스레드 시작
    mainSource.tcpThread = thread(&cServer::tcpCommunication, &mainSource);
  
    motionDiff md(mtx); //움직임 감지 객체
    unsigned long long count1 = 0;
    unsigned long long count2 = 0;
    while (true) {
        // 카메라에서 프레임 가져오기
        {
            unique_lock<mutex> lock(mtx);
            frame = mainSource.getSource();
            md.frameReady = true;
            conv.notify_one();
        }

        mainSource.record(frame);

        //움직임 감지
        if(!md.firstFrame){
            md.standard = frame;
            md.setFrame();
            md.firstFrame = true;
        }
        if(mainSource.power_motion.load()){ //motion detect on
            md.frameUpdate(frame);
            if(md.calcDiff()){
                mainSource.tcpFlag.store(1);
                if(count1 == 10){
                    md.setFilename();
                    imwrite(md.filename + ".png", frame);
                    count1 = 0;
                }
                count1++;
            }
            else mainSource.tcpFlag.store(0);
        }

        // 화재 감지
        if(mainSource.power_fire.load()){
            if(count2 == 100){ //fire detect on
                //fire_detector.detect_from_video(frame); // bool return하도록 수정됨.
                if(fire_detector.detect_from_video(frame)){
                    mainSource.tcpFlag.store(2); //감지O
                    fireCheck = true;
                    running = true;
                }
                else{
                    mainSource.tcpFlag.store(0); //감지x
                    fireCheck = false;
                    running = false;
                } 
                count2 = 0;
            }

            if (fireCheck){
                rectangle(frame, Rect(0, 0, frame.cols, frame.rows), Scalar(0, 0, 255), 3);
                putText(frame, "FIRE", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 255, 255), 2);
            }
            else{
                rectangle(frame, Rect(0, 0, frame.cols, frame.rows), Scalar(0, 255, 0), 3);
                putText(frame, "CLEAR", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 255, 255), 2);
            }
            count2++;
        }
        // tcp 파이프라인에 프레임 전송하기
        if (mainSource.setSource(frame))
        {
            std::cerr << "Error: Unable to grab frame from camera.\n";
        }

        // 테스트 용
        // OpenCV로 로컬 출력
        //cv::imshow("Camera Feed", frame);

        // ESC 키를 누르면 종료
        if (cv::waitKey(1) == 27) {
            mainSource.recordWriter.release();
            std::cout << "Exiting...\n";
            break;
        }
        
    }
    mainSource.recordWriter.release();
  
    return 0;
}
