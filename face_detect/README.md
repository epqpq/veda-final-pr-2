## 설치 및 설정 가이드
### gstreamer 설치
```
sudo apt-get install gstreamer1.0-libcamera libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
```
### dlib 설치
```
sudo git clone https://github.com/davisking/dlib.git
cd dlib
mkdir build
cd build
cmake ..
cmake --build .
cd ..
sudo python3 setup.py install
```
### opencv 설치
```
sudo apt-get install libopencv-dev
```
### face_recognition 설치
```
pip3 install face_recognition
```
## 실행 방법
### 실행
```
python3 face_detect.py
```
## 사용법
인식 하고자 하는 사람의 얼굴 사진을 test_images폴더에 넣은 뒤 카메라로 얼굴을 찍어서 확인.  
**서버와 연결하지 않는 단독 기능입니다.**
## 참조 및 링크
https://github.com/ageitgey/face_recognition/tree/master
