#ifndef _FTP_CLIENT_H_
#define _FTP_CLIENT_H_

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QCoreApplication>
#include <QTimer>
#include <QThread>
#include <QDebug>

#define INTERVAL 360000

class FtpClient : public QObject
{
    Q_OBJECT
public:
    explicit FtpClient(QObject *parent = nullptr);
    ~FtpClient();

    void connectServer(const QString &ftpUrl, const QString &username, const QString &password);
    void downloadFile(const QString &remoteFilePath, const QString &localFilePath);
    void uploadFile(const QString &localFilePath, const QString &remoteFilePath);
    void listDirectory(const QString &directory);
signals:
    void fileDownloaded(const QString &localFilePath);
    void fileUploaded();
    void directoryListed(const QStringList &fileList);

private slots:
    void handleListReply(QNetworkReply *reply);
    void handleDownloadReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QUrl ftpUrl;
};

class FtpMonitor : public QThread {
    Q_OBJECT
public:
    explicit FtpMonitor(QObject *parent = nullptr) : QThread(parent) {}
    ~FtpMonitor() {
        delete client;
    }
    void startMonitoring(const QString& ftpUrl, const QString& username, const QString& password, const QString& remoteDirectory, const QString& localDirectory, int intervalMs = INTERVAL)
    {
        client = new FtpClient();
        this->ftpUrl = ftpUrl;
        this->username = username;
        this->password = password;
        this->remoteDirectory = remoteDirectory;
        this->localDirectory = localDirectory;
        this->intervalMs = intervalMs;
    }

protected:
    void run() override {
        QTimer timer;

        client->connectServer(ftpUrl, username, password);

        connect(client, &FtpClient::directoryListed, this, &FtpMonitor::onDirectoryListed, Qt::QueuedConnection);
        connect(&timer, &QTimer::timeout, [this]() {
            client->listDirectory(remoteDirectory);
        });
        timer.start(intervalMs);

        exec();
    }

private slots:
    void onDirectoryListed(const QStringList &fileList) {
        qDebug() << "check FTP server list";
        if (!prevFileList.isEmpty()) {
            for (const QString &file : fileList) {
                if (!prevFileList.contains(file)) {
                    qDebug() << "New or updated file detected:" << file;
                    QString localFilePath = localDirectory;
                    client->downloadFile(remoteDirectory + "/" + file.trimmed(), localFilePath);
                }
            }
        }
        prevFileList = fileList;
    }

private:
    QString ftpUrl;
    QString username;
    QString password;
    QString remoteDirectory;
    QString localDirectory;
    int intervalMs;
    QStringList prevFileList;
    FtpClient* client;
};


#endif // FTPCLIENT_H
