#include "camera_server.h"
#include "motionDiff.h"

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include <opencv2/core/ocl.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/model.h"
#include <cmath>

using namespace cv;
using namespace std;

const size_t width = 300;
const size_t height = 300;

std::vector<std::string> Labels;
std::unique_ptr<tflite::Interpreter> interpreter;
std::mutex mtx;
std::condition_variable conv;
bool frameReady = false;
bool firstFrame = false;

static bool getFileContent(std::string fileName)
{

	// Open the File
	std::ifstream in(fileName.c_str());
	// Check if object is valid
	if(!in.is_open()) return false;

	std::string str;
	// Read the next line from File untill it reaches the end.
	while (std::getline(in, str))
	{
		// Line contains string of length > 0 then save it in vector
		if(str.size()>0) Labels.push_back(str);
	}
	// Close The File
	in.close();
	return true;
}

void detect_from_video(Mat &src)
{
    Mat image;
    int cam_width =src.cols;
    int cam_height=src.rows;

    // copy image to input as input tensor
    cv::resize(src, image, Size(300,300));
    memcpy(interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

    interpreter->SetAllowFp16PrecisionForFp32(true);
    interpreter->SetNumThreads(2);      //set core

//        cout << "tensors size: " << interpreter->tensors_size() << "\n";
//        cout << "nodes size: " << interpreter->nodes_size() << "\n";
//        cout << "inputs: " << interpreter->inputs().size() << "\n";
//        cout << "input(0) name: " << interpreter->GetInputName(0) << "\n";
//        cout << "outputs: " << interpreter->outputs().size() << "\n";

    interpreter->Invoke();      // run your model

    const float* detection_locations = interpreter->tensor(interpreter->outputs()[0])->data.f;
    const float* detection_classes=interpreter->tensor(interpreter->outputs()[1])->data.f;
    const float* detection_scores = interpreter->tensor(interpreter->outputs()[2])->data.f;
    const int    num_detections = *interpreter->tensor(interpreter->outputs()[3])->data.f;

    //there are ALWAYS 10 detections no matter how many objects are detectable
//        cout << "number of detections: " << num_detections << "\n";

    const float confidence_threshold = 0.5;
    for(int i = 0; i < num_detections; i++){
        if(detection_scores[i] > confidence_threshold){
            int  det_index = (int)detection_classes[i]+1;
            float y1=detection_locations[4*i  ]*cam_height;
            float x1=detection_locations[4*i+1]*cam_width;
            float y2=detection_locations[4*i+2]*cam_height;
            float x2=detection_locations[4*i+3]*cam_width;

            Rect rec((int)x1, (int)y1, (int)(x2 - x1), (int)(y2 - y1));
            rectangle(src,rec, Scalar(0, 0, 255), 1, 8, 0);
            putText(src, format("%s", Labels[det_index].c_str()), Point(x1, y1-5) ,FONT_HERSHEY_SIMPLEX,0.5, Scalar(0, 0, 255), 1, 8, 0);
        }
    }
}

int main(int argc, char** argv)
{
    cServer mainSource;

    int ret = mainSource.init();
    if (ret) {
        perror("Initialization failed\n");
        return 0;
    }

    cv::Mat frame;

    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("detect.tflite");
    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    interpreter->AllocateTensors();

	// Get the names
	bool result = getFileContent("COCO_labels.txt");
	if(!result)
	{
        cout << "loading labels failed";
        exit(-1);
	}

    motionDiff md(mtx); //움직임 감지 객체
    md.startThread(); //소켓 통신 시작

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
        md.frameUpdate(frame);
        md.calcDiff();

        // 화재 감지
        /*
        *
        * 
        * 
        * 
        * 
        * 
        * 
        * 
        * 
        * 
        * 
        */
       //test
       detect_from_video(frame);

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

    return 0;
}
