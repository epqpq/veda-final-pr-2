// #include "tcpclient.h"
// #include "tcpthread.h"
// #include "mainwindow.h"
// #include <QMessageBox>
// #include <QApplication>
// #include <QSslConfiguration>
// #include <QSslCertificate>
// #include <QDebug>
// #include <QFile>
// #include <QDateTime>

// TcpClient::TcpClient(MainWindow* mainWindow, QString& id, QString& ip, int port, QWidget* parent)
//     : QMainWindow(parent), mainWindow(mainWindow), streamingFlag(false), motionFlag(true), fireFlag(true), recordingFlag(true), sendFlag(false), clientID(id), isFireDetected(fireFlag)
// {
//     socket = new QSslSocket(this);
//     thread = new TcpThread(this);

//     // SSL 구성 설정
//     QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
//     QList<QSslCertificate> caCertificates = sslConfig.caCertificates();

//     // 서버 인증서 추가
//     QFile certFile1("C:/certificates/server1.crt");
//     if (!certFile1.open(QIODevice::ReadOnly)) {
//         qCritical() << "Failed to open server certificate file";
//         return;
//     }
//     QSslCertificate serverCert1(&certFile1, QSsl::Pem);
//     certFile1.close();
//     if (serverCert1.isNull()) {
//         qCritical() << "Failed to load server certificate";
//         return;
//     }
//     caCertificates.append(serverCert1);

//     QFile certFile2("C:/certificates/server2.crt");
//     if (!certFile2.open(QIODevice::ReadOnly)) {
//         qCritical() << "Failed to open server certificate file";
//         return;
//     }
//     QSslCertificate serverCert2(&certFile2, QSsl::Pem);
//     certFile2.close();
//     if (serverCert2.isNull()) {
//         qCritical() << "Failed to load server certificate";
//         return;
//     }
//     caCertificates.append(serverCert2);

//     QFile certFile3("C:/certificates/server3.crt");
//     if (!certFile3.open(QIODevice::ReadOnly)) {
//         qCritical() << "Failed to open server certificate file";
//         return;
//     }
//     QSslCertificate serverCert3(&certFile3, QSsl::Pem);
//     certFile3.close();
//     if (serverCert3.isNull()) {
//         qCritical() << "Failed to load server certificate";
//         return;
//     }
//     caCertificates.append(serverCert3);


//     QFile certFile4("C:/certificates/server4.crt");
//     if (!certFile4.open(QIODevice::ReadOnly)) {
//         qCritical() << "Failed to open server certificate file";
//         return;
//     }
//     QSslCertificate serverCert4(&certFile4, QSsl::Pem);
//     certFile4.close();
//     if (serverCert4.isNull()) {
//         qCritical() << "Failed to load server certificate";
//         return;
//     }
//     caCertificates.append(serverCert4);

//     sslConfig.setCaCertificates(caCertificates);
//     sslConfig.setPeerVerifyMode(QSslSocket::VerifyPeer); // SSL 인증서 검증 활성화
//     socket->setSslConfiguration(sslConfig);

//     connectTcpServer(ip, port);
// }

// TcpClient::~TcpClient()
// {
//     delete mainWindow;
//     delete thread;
//     delete socket;
// }

// bool TcpClient::connectTcpServer(const QString& ip, int port)
// {
//     socket->connectToHostEncrypted(ip, port);

//     if (!socket->waitForEncrypted() || socket->state() != QAbstractSocket::ConnectedState) {
//         qDebug() << "SSL encryption failed: " << socket->errorString();
//         return false;
//     }
//     thread->setSocket(socket);
//     connect(thread, &TcpThread::recvComplete, this, &TcpClient::recvEvent);
//     connect(thread, &TcpThread::writeComplete, this, &TcpClient::writeComplete);

//     return true;
// }

// bool TcpClient::writeEvent(const char* event)
// {
//     bool state = socket->state() == QAbstractSocket::ConnectedState;

//     if (state) {
//         thread->writeData(event);
//         return true;
//     }
//     else {
//         return false;
//     }
// }

// bool TcpClient::recvEvent(const char* event)
// {
//     QString recvEvent = QString::fromUtf8(event);
//     qDebug() << "Received data: " << recvEvent;

//     QStringList splitResult = recvEvent.split(";");
//     if (splitResult.size() != 2) {
//         qDebug() << "Invalid data format";
//         return false;
//     }

//     QString type = splitResult.at(0);
//     QString eventType = splitResult.at(1);

//     qDebug() << "Type: " << type << ", Event Type: " << eventType;

//     if (type == "1") {
//         if (eventType == "fire") {
//             handleFireDetect();
//         }
//         else if (eventType == "motion") {
//             handleMotionDetect();
//         }
//         else {
//             qDebug() << "Unknown event type";
//             return false;
//         }
//     }
//     else {
//         qDebug() << "Unknown Detect type";
//         return false;
//     }

//     return true;
// }

// void TcpClient::writeComplete(const char* data)
// {
//     Q_UNUSED(data);
//     qDebug() << "Data successfully written to the server";
// }

// void TcpClient::recvComplete(const char* data)
// {
//     Q_UNUSED(data);
// }

// bool TcpClient::pushButtonMotionDetectOnOff()
// {
//     QString sendData;
//     if (motionFlag) {
//         sendData = "2;motion;off";
//     }
//     else {
//         sendData = "2;motion;on";
//     }

//     sendFlag = writeEvent(sendData.toStdString().c_str());
//     if (!sendFlag) {
//         qDebug() << "Fail to send";
//         return false;
//     }
//     motionFlag = !motionFlag;
//     return true;
// }

// bool TcpClient::pushButtonFireDetectOnOff()
// {
//     QString sendData;
//     if (fireFlag) {
//         sendData = "2;fire;off";
//     }
//     else {
//         sendData = "2;fire;on";
//     }

//     sendFlag = writeEvent(sendData.toStdString().c_str());
//     if (!sendFlag) {
//         qDebug() << "Fail to send";
//         return false;
//     }
//     fireFlag = !fireFlag;
//     return true;
// }

// bool TcpClient::pushButtonRecording()
// {
//     QString sendData;
//     if (recordingFlag) {
//         sendData = "2;recording;off";
//     }
//     else {
//         sendData = "2;recording;on";
//     }

//     sendFlag = writeEvent(sendData.toStdString().c_str());
//     if (!sendFlag) {
//         qDebug() << "Fail to send";
//         return false;
//     }

//     recordingFlag = !recordingFlag;
//     return true;
// }

// void TcpClient::handleMotionDetect()
// {
//     qDebug() <<  "check handler";
//     QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//     QString message = QString("로그 메시지 : ID = %1, 발생시간 = %2, 이벤트 = Motion Detected").arg(clientID).arg(currentTime);
//     mainWindow->appendLogMessage(message);
//     // QString message = QString("%1 Motion detected!").arg(clientID);
//     // QMessageBox::warning(this, "Motion Detection Alert", message);
// }

// void TcpClient::handleFireDetect()
// {
//     // QString message = QString("%1 Fire detected!").arg(clientID);
//     // QMessageBox::warning(this, "Fire Detection Alert", message);
//     QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//     QString message = QString("로그 메시지 : ID = %1, 발생시간 = %2, 이벤트 = Fire Detected").arg(clientID).arg(currentTime);
//     mainWindow->appendLogMessage(message);
// }


