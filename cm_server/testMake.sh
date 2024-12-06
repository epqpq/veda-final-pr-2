#!/bin/bash
##g++ -o main camera_server.cpp camera_server_main.cpp `pkg-config --libs --cflags opencv4 gstreamer-1.0 gstreamer-app-1.0 gstreamer-rtsp-server-1.0`

g++ -o main camera_server.cpp camera_server_main.cpp motionDiff.cpp fire_detector.cpp `pkg-config --libs --cflags opencv4 gstreamer-1.0 gstreamer-app-1.0` -ltensorflow-lite -lssl -lcrypto
