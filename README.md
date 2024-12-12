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
WiringPi 3.10  
Dlib 19.24.99
## 설치 및 설정 가이드
### tensorflow-lite 설치
Execute the following command to download the .deb package from releases page of the repository:
```
wget https://github.com/prepkg/tensorflow-lite-raspberrypi/releases/latest/download/tensorflow-lite_64.deb
```
When the download is finished, install TensorFlow Lite:
```
sudo apt install -y ./tensorflow-lite_64.deb
```
You can remove .deb package because no longer needed:
```
rm -rf tensorflow-lite_64.deb
```
### opencv 설치
```
sudo apt-get install libopencv-dev
```
### gstreamer 설치
```
sudo apt-get install gstreamer1.0-libcamera libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
```
### openssl 설치
```
sudo apt install libssl-dev
```
### WiringPi 설치
```
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build debian
cd debian-template
sudo apt install wiringpi_3.10_arm64.deb
```
## 빌드 및 실행 방법
### 빌드
```
cd cm_server
make
```
### 실행
```
./main
```
## 사용법
카메라 서버 프로그램을 실행하고 클라이언트에서 접속을 요청하면 카메라가 켜지고 클라이언트에서 영상을 볼 수 있다.  
클라이언트에서 움직임 감지와 화재 감지 기능을 끄고 켤 수 있다.
## 동작 예제
## 문제 해결
### 프로그램 빌드 시 opencv를 찾지 못하는 문제
pkg-config가 설치되지 않아서 발생하는 문제이다.  
아래 방법대로 설치 후 재빌드하면 해결된다.
```
sudo apt install pkg-config
```
## 기여 방법
## 라이선스
## 참조 및 링크
