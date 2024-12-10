# 프로젝트 이름
## 개요
## 목차
## 프로젝트 아키텍처 및 구조
## 테스트 환경
보드: 라즈베리파이 5  
카메라: raspberry pi camera module v1  
OS: debian gnu/linux 12 (bookworm)  
tensorflow-lite 2.18  
opencv 4.10.0  
flatbuffers 24.3.25
gstreamer 1.22.0  
openssl 3.0.15
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
python3 run.py
```
## 사용법
인식 하고자 하는 사람의 얼굴 사진을 test_images폴더에 넣은 뒤 카메라로 얼굴을 찍어서 확인.
## 동작 예제
## 문제 해결
## 기여 방법
## 라이선스
## 참조 및 링크
