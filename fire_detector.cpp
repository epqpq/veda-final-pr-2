#include "fire_detector.h"

FireDetector::FireDetector(){
    cerr << "Error: please generate with model path" << "\n";
    exit(1);
}

FireDetector::FireDetector(const char* model_path){
    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(model_path);
    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    interpreter->AllocateTensors();
}

bool FireDetector::detect_from_video(Mat &src){
    Mat image;

    // copy image to input as input tensor
    cv::resize(src, image, Size(224,224));
    image.convertTo(image, CV_32FC3); // convert to float32
    memcpy(interpreter->typed_input_tensor<float>(0), image.data, image.total() * image.elemSize());

    interpreter->SetAllowFp16PrecisionForFp32(true);
    //interpreter->SetNumThreads(2);      //set core

    interpreter->Invoke();      // run your model

    const float* output = interpreter->tensor(interpreter->outputs()[0])->data.f; 
    if (output == nullptr) {
        cerr << "Error: Output tensor data is null." << endl;
        exit(1);
    }

    // 출력 텐서 크기 확인
    auto output_tensor = interpreter->tensor(interpreter->outputs()[0]);
    int output_size = output_tensor->dims->data[1]; // 출력 클래스의 개수
    
    // for (int i = 0; i < output_size; i++) {
    //     cout << "Class " << i << ": " << output[i] << "\n";
    // }

    if (output[0]>0.5) { // FIRE class
        // rectangle(src, Rect(0, 0, src.cols, src.rows), Scalar(0, 0, 255), 3);
        // putText(src, "FIRE", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 255, 255), 2);
        return true;
    } else { // CLEAR class
        // rectangle(src, Rect(0, 0, src.cols, src.rows), Scalar(0, 255, 0), 3);
        // putText(src, "CLEAR", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 255, 255), 2);
        return false;
    }
}