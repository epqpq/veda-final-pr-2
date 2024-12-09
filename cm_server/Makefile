# Compiler
CXX = g++

# Libraries
PKG_CONFIG_LIBS = `pkg-config --libs --cflags opencv4 gstreamer-1.0 gstreamer-app-1.0`
LIBS = -ltensorflow-lite -lssl -lcrypto -lwiringPi -pthread $(PKG_CONFIG_LIBS)

# Source files
SRCS = camera_server.cpp camera_server_main.cpp motionDiff.cpp fire_detector.cpp
# Object files (auto-generated from SRCS)
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = main

# Default rule
all: $(TARGET)

# Link objects to create the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(LIBS)

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
	rm *png

.PHONY: all clean