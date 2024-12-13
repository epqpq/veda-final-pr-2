#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <QWidget>
#include <memory>
#include "gstreamerclient.h"
#include "gstreamerclientthread.h"
#include "tcpthread.h"

#define TCP_PORT       5100
#define GSTREAMER_PORT 5000

class Client : public QWidget {
    Q_OBJECT
public:
    explicit Client(QWidget* parent = nullptr);
    ~Client();

    void configureClient(const QString& pipeline, const QString& ip, const QString& id);
    bool connectToServer();
    void disconnectFromServer();
    bool sendEvent(const QString& event);
    bool getStreamingStatus() const;
    QString getClientID() const;
    QString getServerIp() const;
    GstreamerClient* getGstreamerClient() const;
    GstreamerClientThread* getGstreamerClientThread() const;
    void setGstreamerClient(GstreamerClient* client);
    void setGstreamerClientThread(GstreamerClientThread* thread);
    bool setRecordOnOff();
    bool setMotionDetectOnOff();
    bool setFireDetectOnOff();
signals:
    void dataReceived(const QString& data);
    void errorOccurred(const QString& error);
    void handleLogMessage(const QString& message);    // 발생한 event 전달 시그널
    void clientDisconnected(const QString& clientID); // gstreamer가 연결이 끊겼을때 전달 시그널
private slots:
    void handleDataReceived(const QString& data);
    void handleError(const QString& error);
    void handleStreamingStopped(const QString& reason);
private:
    std::shared_ptr<GstreamerClient> gstreamerClient;
    std::shared_ptr<TcpThread> tcpClient;
    std::shared_ptr<GstreamerClientThread> gstreamerThread;
    QString clientPipeline;                 // GStreamer 파이프라인 문자열
    QString clientIP;                       // 클라이언트 IP
    QString clientID;                       // 클라이언트 ID
    int tcpPort;                            // TCP 포트 번호
    int gstreamerPort;                      // GStreamer 포트 번호
    bool streamingStatus;                   // 스트리밍 상태
    bool motionDetectFlag;
    bool fireDetectFlag;
    bool recordFlag;
};


#endif
