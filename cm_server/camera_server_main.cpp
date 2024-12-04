#include "camera_server.h"
#include "motionDiff.h"
#include "fire_detector.h"

using namespace cv;
using namespace std;

std::vector<std::string> Labels;
std::mutex mtx;
std::condition_variable conv;
bool frameReady = false;
bool firstFrame = false;

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
    //mainSource.tcpThread = thread(&cServer::tcpCommunication, &mainSource);

    motionDiff md(mtx); //움직임 감지 객체

    while (true) {
        // 카메라에서 프레임 가져오기
        {
            unique_lock<mutex> lock(mtx);
            frame = mainSource.getSource();
            frameReady = true;
            conv.notify_one();
        }
        
        // 움직임 감지
        if(!firstFrame){
            md.standard = frame;
            md.setFrame();
            firstFrame = true;
        }
        if(mainSource.power_motion.load()){ //motion detect on
            md.frameUpdate(frame);
            if(md.calcDiff())
               mainSource.tcpFlag.store(1); 
            else mainSource.tcpFlag.store(0);
        }

        // 화재 감지
        if(mainSource.power_fire.load()){ //fire detect on
            fire_detector.detect_from_video(frame); // bool return하도록 수정됨.
            // if(md.화재감지함수){
            //     mainSource.tcpFlag.store(2); //감지O
            // }
            // else mainSource.tcpFlag.store(0); //감지x
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
            std::cout << "Exiting...\n";
            break;
        }
    }

    gst_element_set_state(mainSource.pipeline, GST_STATE_NULL);
    gst_object_unref(mainSource.pipeline);
    
    return 0;
}
