#!/bin/bash
##g++ -o main camera_server.cpp camera_server_main.cpp `pkg-config --libs --cflags opencv4 gstreamer-1.0 gstreamer-app-1.0 gstreamer-rtsp-server-1.0`

g++ -o main camera_server.cpp camera_server_main.cpp `pkg-config --libs --cflags opencv4 gstreamer-1.0 gstreamer-app-1.0 gstreamer-rtsp-server-1.0` -L/home/pi/flatbuffers/build -lflatbuffers -ltensorflow-lite