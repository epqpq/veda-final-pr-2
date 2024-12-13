#ifndef _TCP_THREAD_H_
#define _TCP_THREAD_H_

#include <QThread>
#include <QSslSocket>
#include <QMutex>
#include <QWaitCondition>

class TcpThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpThread(QObject* parent = nullptr);
    ~TcpThread();

    void setServerConfig(const QString& host, int port);
    bool connectToServer();
    bool sendData(const QString& data);
    void stop();
signals:
    void dataReceived(const QString& data);
    void errorOccurred(const QString& error);

protected:
    void run() override;

private slots:
    void handleDataRead();
    void handleError(QAbstractSocket::SocketError socketError);

private:
    QSslSocket* socket;                 // SSL을 지원하는 socket
    QString ip;                         // server IP
    int port;                           // server port
    QMutex mutex;                       // mutex
    QWaitCondition waitCondition;
    bool running;                       // thread 실행 상태
    QString dataBuffer;                 // 전송 중인 데이터를 저장

    void configureSslCertificates();    // SSL 인증서 설정
};

#endif // TCPTHREAD_H
