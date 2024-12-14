## 테스트 환경
OS: Window 11  
QT: 6.8.1 - MSVC 2022 64-bit  
build version: MinGW 13.1.0 64-bit

## 설치 및 사용 방법
클라이언트 코드를 실행하기 위해서는 QT creator 프로그램이 필요합니다. 
### Gstreamer 설치
https://gstreamer.freedesktop.org/download/#windows MSVC 64-bit runtime installer와 development installer 설치
### QT 추가 요소 설치
C:\Qt\MaintenanceTool.exe 실행 -> 로그인 -> 구성요소 추가 또는 제거 -> Qt (-> Qt Multimedia, Qt Quick 3D, Qt Quick Timeline, Qt Shader Tools, Build Tools -> OpenSSL 3.0.15 Toolkit) 설치
### 환경 변수 설정
윈도우 창 -> 시스템 환경 변수 편집 -> 고급 -> 환경 변수 -> 시스템 변수 
기존 PATH에 C:\gstreamer\1.0\msvc_x86_64\bin 추가  
PKG_CONFIG_PATH 이름으로 변수 새로 만든 후 -> C:\gstreamer\1.0\msvc_x86_64\lib\pkgconfig 추가   
GSTREAMER_1_0_ROOT_MSVC_X86_64 이름으로 변수 새로 만든 후 -> C:\gstreamer\1.0\msvc_x86_64\ 추가
### 인증서 추가 방법 
인증서 생성에 대한 설명은 cm_server의 README 파일에서 확인하실 수 있으며, 인증서 생성이 완료 된 경우 아래 작업을 수행해 주시길 바랍니다.  

tcpthread.cpp의 131번째 줄 코드 중 crt 파일의 경로를 지정하는 코드를 직접 수정해 주시거나, C:/certificates/폴더를 생성한 뒤 server1.crt로 저장해주시면 됩니다. 

![image](https://github.com/user-attachments/assets/84efaf70-d6f6-4a70-8c41-339a9589304a)

또는

<img src="https://github.com/user-attachments/assets/12edca2d-9156-4037-bde6-ad5561e8eed9" />

![image](https://github.com/user-attachments/assets/67da6701-38cd-47c8-92bf-f8407267c7a1)
