#include "camera_server.h"
#include "motionDiff.h"
#include "fire_detector.h"

using namespace cv;
using namespace std;

std::vector<std::string> Labels;
std::mutex mtx;
std::condition_variable conv;

int main(int argc, char** argv)
{
    cServer mainSource;
    FireDetector fire_detector("firenet.tflite");

    int ret = mainSource.init();
    if (ret) {
        perror("Initialization failed\n");
        return 0;
    }

    cv::Mat frame;
    
    //스레드 시작
    mainSource.tcpThread = thread(&cServer::tcpCommunication, &mainSource);
  
    motionDiff md(mtx); //움직임 감지 객체
    unsigned long long count = 0;
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
            if(md.calcDiff())
               mainSource.tcpFlag.store(1); 
            else mainSource.tcpFlag.store(0);
        }

        // 화재 감지
        if((count == 1000) && mainSource.power_fire.load()){ //fire detect on
            //fire_detector.detect_from_video(frame); // bool return하도록 수정됨.
            if(fire_detector.detect_from_video(frame)){
                mainSource.tcpFlag.store(2); //감지O
            }
            else mainSource.tcpFlag.store(0); //감지x
            count = 0;
        }

        // tcp 파이프라인에 프레임 전송하기
        if (mainSource.setSource(frame))
        {
            std::cerr << "Error: Unable to grab frame from camera.\n";
        }

        // 테스트 용
        // OpenCV로 로컬 출력
        cv::imshow("Camera Feed", frame);

        // ESC 키를 누르면 종료
        if (cv::waitKey(1) == 27) {
            mainSource.recordWriter.release();
            std::cout << "Exiting...\n";
            break;
        }
        count++;
    }
    mainSource.recordWriter.release();
  
    return 0;
}
