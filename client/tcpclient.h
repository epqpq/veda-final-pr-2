// #ifndef _TCP_CLIENT_H_
// #define _TCP_CLIENT_H_

// #include <QMainWindow>
// #include <QSslSocket>

// class TcpThread;
// class MainWindow;

// class TcpClient : public QMainWindow {
//     Q_OBJECT
// public:
//     TcpClient(MainWindow* mainWindow, QString& id, QString& ip, int port, QWidget* parent = nullptr);
//     ~TcpClient();

//     bool connectTcpServer(const QString& ip, int port);
//     bool writeEvent(const char* event);
//     bool recvEvent(const char* event);
//     bool pushButtonMotionDetectOnOff();
//     bool pushButtonFireDetectOnOff();
//     bool pushButtonRecording();
// private slots:
//     void writeComplete(const char* data);
//     void recvComplete(const char* data);
// private:
//     void handleMotionDetect();
//     void handleFireDetect();

//     QSslSocket* socket;
//     TcpThread* thread;
//     MainWindow* mainWindow;

//     QString clientIP;
//     QString clientID;
//     int clientPort;
//     bool connectFlag;
//     bool streamingFlag;
//     bool motionFlag;
//     bool fireFlag;
//     bool recordingFlag;
//     bool sendFlag;
//     bool isFireDetected;
// };

// #endif // TCPCLIENT_H
