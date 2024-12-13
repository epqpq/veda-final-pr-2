#include "tcpthread.h"
#include <QDebug>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <QDebug>
#include <QFile>
#include <QDateTime>

TcpThread::TcpThread(QObject* parent) : QThread(parent), socket(nullptr), port(0), running(false)
{

}

TcpThread::~TcpThread()
{
    stop();
}

void TcpThread::setServerConfig(const QString& ip, int port)
{
    QMutexLocker locker(&mutex);
    this->ip = ip;
    this->port = port;
}

bool TcpThread::connectToServer()
{
    QMutexLocker locker(&mutex);
    // SSL을 지원하는 socket 생성
    socket = new QSslSocket();
    // data 도착 시 handleReadyRead 호출
    connect(socket, &QSslSocket::readyRead, this, &TcpThread::handleDataRead);
    // socket error 발생 시 handleError 호출
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QSslSocket::errorOccurred), this, &TcpThread::handleError);

    // server에 연결 요청
    socket->connectToHostEncrypted(ip, port);
    if (!socket->waitForEncrypted(5000)) {
        emit errorOccurred("Failed to establish SSL connection, Error message : " + socket->errorString());
        delete socket;
        socket = nullptr;
        return false;
    }
    return true;
}

bool TcpThread::sendData(const QString& data)
{
    QMutexLocker locker(&mutex);

    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        qint64 bytesWritten = socket->write(data.toUtf8());
        if (bytesWritten == -1) {
            emit errorOccurred("Failed to write data to socket : " + socket->errorString());
            return false;
        }
        return true;
    }
    else {
        emit errorOccurred("Socket is not connected. Cannot send data.");
        return false;
    }
}

// thread 실행 종료
void TcpThread::stop()
{
    QMutexLocker locker(&mutex);
    running = false;
    waitCondition.wakeAll();
}

// thread 실행 시작
void TcpThread::run()
{
    QMutexLocker locker(&mutex);
    running = true;

    if (!connectToServer()) {
        return;
    }

    while (running) {
        // 전송할 데이터가 있는 경우에는 데이터 전송
        if (!dataBuffer.isEmpty() && socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(dataBuffer.toUtf8());
            socket->waitForBytesWritten();
            dataBuffer.clear();
        }
        waitCondition.wait(&mutex, 100);
    }

    // socket 연결 해제
    socket->disconnectFromHost();
    socket->waitForDisconnected();
    delete socket;
    socket = nullptr;
}

// server에서 수신된 데이터 읽기
void TcpThread::handleDataRead()
{
    if (socket) {
        QString data = QString::fromUtf8(socket->readAll());


        emit dataReceived(data);
    }
}

// socket error 발생 시 error 처리
void TcpThread::handleError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit errorOccurred(socket->errorString());
}

void TcpThread::configureSslCertificates()
{
    if (!socket) {
        qCritical() << "Socket is null, cannot configure SSL certificates.";
        return;
    }

    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    QList<QSslCertificate> caCertificates = sslConfig.caCertificates();

    QStringList certificateFiles = {
        "C:/certificates/server1.crt",
        "C:/certificates/server2.crt",
        "C:/certificates/server3.crt",
        "C:/certificates/server4.crt"
    };

    for (const QString& certFilePath : certificateFiles) {
        QFile certFile(certFilePath);
        if (!certFile.open(QIODevice::ReadOnly)) {
            qCritical() << "Failed to open server certificate file:" << certFilePath;
            continue;
        }

        QSslCertificate serverCert(&certFile, QSsl::Pem);
        certFile.close();

        if (serverCert.isNull()) {
            qCritical() << "Failed to load server certificate from file:" << certFilePath;
            continue;
        }

        caCertificates.append(serverCert);
    }

    sslConfig.setCaCertificates(caCertificates);
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyPeer);    // SSL 인증서 검증 활성화
    socket->setSslConfiguration(sslConfig);
}
