## 테스트 환경
OS: Window 11  
QT: 6.8.1 - MSVC 2022 64-bit  
build version: MinGW 13.1.0 64-bit

클라이언트 코드를 실행하기 위해서는 QT creator 프로그램이 필요합니다. 

https://gstreamer.freedesktop.org/download/#windows MSVC 64-bit runtime installer와 development installer 설치

C:\Qt\MaintenanceTool.exe 실행 -> 로그인 -> 구성요소 추가 또는 제거 -> Qt (-> Qt Multimedia, Qt Quick 3D, Qt Quick Timeline, Qt Shader Tools, Build Tools -> OpenSSL 3.0.15 Toolkit) 설치

윈도우 창 -> 시스템 환경 변수 편집 -> 고급 -> 환경 변수 -> 시스템 변수 
기존 PATH에 C:\gstreamer\1.0\msvc_x86_64\bin 추가  
PKG_CONFIG_PATH 이름으로 변수 새로 만든 후 -> C:\gstreamer\1.0\msvc_x86_64\lib\pkgconfig 추가   
GSTREAMER_1_0_ROOT_MSVC_X86_64 이름으로 변수 새로 만든 후 -> C:\gstreamer\1.0\msvc_x86_64\ 추가

**인증서 추가 방법**  
tcpthread.cpp의 128번째 줄에 서버에서 생성한 crt파일의 경로를 지정해야 서버와 통신 가능.
