클라이언트 코드를 실행하기 위해서는 QT creator 프로그램이 필요합니다. 

https://gstreamer.freedesktop.org/download/#windows MSVC 64-bit runtime installer development installer 설치

윈도우 창 -> 시스템 환경 변수 편집 -> 고급 -> 환경 변수 -> 시스템 변수 
기존 PATH에 C:\gstreamer\1.0\msvc_x86_64\bin 추가
PKG_CONFIG_PATH 이름으로 변수 새로 만든 후 -> C:\gstreamer\1.0\msvc_x86_64\lib\pkgconfig 추가
GSTREAMER_1_0_ROOT_MSVC_X86_64 이름으로 변수 새로 만든 후 -> C:\gstreamer\1.0\msvc_x86_64\ 추가

**인증서 추가 방법**  
tcpthread.cpp의 128번째 줄에 서버에서 생성한 crt파일의 경로를 지정해야 서버와 통신 가능.
