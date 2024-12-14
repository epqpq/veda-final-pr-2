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
![image](https://github.com/user-attachments/assets/e3d9ae44-fd4b-4bd1-9c41-731cfb5a2e1e)

![image](https://github.com/user-attachments/assets/f2679828-11c9-4301-8a49-103af7d4dff8)

### 환경 변수 설정
윈도우 창 -> 시스템 환경 변수 편집 -> 고급 -> 환경 변수 -> 시스템 변수 
![path_how](https://github.com/user-attachments/assets/0deb9d0f-21a2-4bfb-84d3-79165b025b68)

기존 PATH에 C:\gstreamer\1.0\msvc_x86_64\bin 추가  
새로 만들기 -> 변수 이름: PKG_CONFIG_PATH 입력 -> 변수 값: C:\gstreamer\1.0\msvc_x86_64\lib\pkgconfig 입력   
새로 만들기 -> 변수 이름: GSTREAMER_1_0_ROOT_MSVC_X86_64 입력 -> 변수 값: C:\gstreamer\1.0\msvc_x86_64\ 입력  
### 인증서 추가 방법 
인증서 생성에 대한 설명은 cm_server의 README 파일에서 확인하실 수 있으며, 인증서 생성이 완료 된 경우 아래 작업을 수행해 주시길 바랍니다.  

tcpthread.cpp의 131번째 줄 코드 중 crt 파일의 경로를 지정하는 코드를 직접 수정해 주시거나, C:/certificates/폴더를 생성한 뒤 server1.crt로 저장해주시면 됩니다. 

![image](https://github.com/user-attachments/assets/84efaf70-d6f6-4a70-8c41-339a9589304a)

또는

<img src="https://github.com/user-attachments/assets/12edca2d-9156-4037-bde6-ad5561e8eed9" />

![image](https://github.com/user-attachments/assets/67da6701-38cd-47c8-92bf-f8407267c7a1)

### 사용 방법
이후 QT creator를 통해 빌드하게되면 다음과 같은 화면이 뜨게 됩니다. 
![image](https://github.com/user-attachments/assets/3b21b1fe-ba5a-47b1-86c5-cf437f0856bf)

우측 상단의 CCTV 레이블을 펼친 뒤 추가 버튼을 클릭하면 등록하고자 하는 카메라의 이름과 ip 주소를 입력하는 창이 뜨게 됩니다.
![image](https://github.com/user-attachments/assets/51739afb-55a7-4774-b403-7f875145b9a8)

추가 버튼을 통해 카메라를 등록하면 기본적으로 네트워크 연결은 끊어져 있는 상태입니다.
카메라로 사용하는 장치에 미리 옮겨둔 cm_server 폴더의 main을 실행시킨 후 연결 버튼을 누르면, connect 상태가 Not Connected에서 Connected로 바뀌고 CCTV 레이블에서 +버튼을 통해 연결된 카메라의 목록을 확인할 수 있게 됩니다.
![image](https://github.com/user-attachments/assets/56aa65d9-0c9c-490d-beeb-556e6b4e025a)

![image](https://github.com/user-attachments/assets/c3416af7-6781-4eb5-ab21-f34f71872989)

목록에 있는 카메라를 클릭해서 연결된 화면을 송출할 수 있고, -버튼을 통해 제거할 수 있습니다.  
또한 송출 화면을 클릭하면 해당 화면을 전체 화면으로 변경할 수 있고, 다시 클릭해서 원 상태로 되돌릴 수 있습니다.
![image](https://github.com/user-attachments/assets/eb3d351f-b328-4d4e-8870-9eb8aab53eb0)

![image](https://github.com/user-attachments/assets/f3e8d16f-5fed-460c-8a5d-e9c17ad0ba30)

기능 설정은 카메라 이름 변경, ip 주소 변경, 움직임 감지, 화재 감지, 녹화등의 기능을 on/off 하는 창입니다.
![image](https://github.com/user-attachments/assets/e646f703-610b-4cba-8018-3d9b17c9c7f7)  

기능 on/off 여부는 장치 화면에서 확인할 수 있습니다.  
![image](https://github.com/user-attachments/assets/d5f12615-2cdb-4aa8-a7ac-594f2b509286)

로그는 움직임 감지, 화재 감지 등의 이벤트가 발생하면 포착된 카메라의 이름과 시각 정보를 기록하여 출력하는 창입니다.  
![image](https://github.com/user-attachments/assets/f3391ded-f8e6-48b6-8c0e-e38be92b4ad3)

녹화 영상 확인은 로컬에 저장된 영상을 재생할 수 있는 동영상 플레이어입니다.

FTP 기능은 카메라에 저장된 영상을 주기적으로 클라이언트에 보내는 기능을 위한 설정 창입니다. 추후 업데이트 예정입니다.

