#include "client.h"
#include <QDebug>

Client::Client(QWidget* parent)
    : QWidget(parent), tcpPort(TCP_PORT), gstreamerPort(GSTREAMER_PORT), streamingStatus(false),
    motionDetectFlag(true), fireDetectFlag(true), recordFlag(true)
{

}

Client::~Client()
{
    qDebug() << "delete client";
    if (gstreamerThread && gstreamerThread->isRunning()) {
        gstreamerThread->requestInterruption();
        gstreamerThread->wait();
    }
}

void Client::configureClient(const QString& pipeline, const QString& ip, const QString& id)
{
    clientPipeline = pipeline;
    clientIP = ip;
    clientID = id;

    gstreamerClient = std::make_shared<GstreamerClient>();
    tcpClient = std::make_shared<TcpThread>();

    gstreamerClient->setGstreamerClient(clientPipeline, clientID);
    tcpClient->setServerConfig(clientIP, tcpPort);

    connect(tcpClient.get(), &TcpThread::dataReceived, this, &Client::handleDataReceived);
    connect(tcpClient.get(), &TcpThread::errorOccurred, this, &Client::handleError);
    connect(gstreamerClient.get(), &GstreamerClient::streamingStopped, this, &Client::handleStreamingStopped);
}

bool Client::connectToServer()
{
    // GStreamer pipeline 연결 및 실행
    if (gstreamerClient) {
        gstreamerThread = std::make_shared<GstreamerClientThread>(gstreamerClient.get(), this);
        gstreamerThread->start();
    }
    else {
        qWarning() << "GStreamer client not initialized";
        return false;
    }
    // TCP server 연결
    if (!tcpClient || !tcpClient->connectToServer()) {
        qWarning() << "TCP connection failed";
        return false;
        // return true;
    }

    streamingStatus = true;
    return true;
}

void Client::handleDataReceived(const QString& event)
{
    qDebug() << "Data received from server :" << event;

    QStringList splitResult = event.split(";");
    if (splitResult.size() != 2) {
        qDebug() << "Invalid data format";
        return;
    }

    QString orderType = splitResult.at(0);
    QString eventType = splitResult.at(1);
    QString eventLog;

    if (orderType == "1") {
        QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        if (eventType == "fire") {
            eventLog = QString("로그 메시지 : ID = %1, 발생시간 = %2, 이벤트 = Fire Detected").arg(clientID).arg(currentTime);
        }
        else if (eventType == "motion") {
            eventLog = QString("로그 메시지 : ID = %1, 발생시간 = %2, 이벤트 = Motion Detected").arg(clientID).arg(currentTime);
        }
        else {
            qDebug() << "Unknown event type";
            return;
        }
    }
    else {
        qDebug() << "Unknown Detect type";
        return;
    }

    emit handleLogMessage(eventLog);
}

void Client::handleError(const QString& error)
{
    qWarning() << "(TCP)Error occurred :" << error;
}

bool Client::sendEvent(const QString& event)
{
    if (!tcpClient) {
        qWarning() << "TCP client not initialized";
        return false;
    }

    return tcpClient->sendData(event);
}

bool Client::getStreamingStatus() const
{
    return streamingStatus;
}

QString Client::getClientID() const
{
    return clientID;
}

QString Client::getServerIp() const
{
    return clientIP;
}

GstreamerClient* Client::getGstreamerClient() const
{
    return gstreamerClient.get();
}

GstreamerClientThread* Client::getGstreamerClientThread() const
{
    return gstreamerThread.get();
}

void Client::setGstreamerClient(GstreamerClient* client)
{
    gstreamerClient.reset(client);
}
\
void Client::setGstreamerClientThread(GstreamerClientThread* thread)
{
    gstreamerThread.reset(thread);
}

bool Client::setMotionDetectOnOff()
{
    QString event = motionDetectFlag ? "2;motion;off" : "2;motion;on";

    if (!tcpClient->sendData(event)) {
        qDebug() << "Failed to send motion detection event.";
        return false;
    }

    motionDetectFlag = !motionDetectFlag;
    return true;
}

bool Client::setFireDetectOnOff()
{
    QString event = fireDetectFlag ? "2;fire;off" : "2;fire;on";

    if (!tcpClient->sendData(event)) {
        qDebug() << "Failed to send fire detection event.";
        return false;
    }

    fireDetectFlag = !fireDetectFlag;
    return true;
}

bool Client::setRecordOnOff()
{
    QString event = recordFlag ? "2;record;off" : "2;record;on";

    if (!tcpClient->sendData(event)) {
        qDebug() << "Failed to send record event.";
        return false;
    }

    recordFlag = !recordFlag;
    return true;
}

void Client::handleStreamingStopped(const QString& reason)
{
    qDebug() << "Streaming stopped for client ID:" << clientID << ", Reason:" << reason;
    emit clientDisconnected(clientID);
}
