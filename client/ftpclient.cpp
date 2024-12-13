#include "ftpclient.h"
#include <QDebug>
#include <QFile>
#include <QNetworkRequest>

FtpClient::FtpClient(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this)) {}

FtpClient::~FtpClient() {}

void FtpClient::connectServer(const QString &ftpUrl, const QString &username, const QString &password)
{
    this->ftpUrl = QUrl(ftpUrl);
    this->ftpUrl.setUserName(username);
    this->ftpUrl.setPassword(password);
    qDebug() << "Connected to FTP server:" << this->ftpUrl.toString();
}

void FtpClient::listDirectory(const QString &directory)
{
    QUrl url = ftpUrl;
    url.setPath(directory);

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { handleListReply(reply); });
}

void FtpClient::downloadFile(const QString &remoteFilePath, const QString &localFilePath)
{
    QUrl url = ftpUrl;
    url.setPath(remoteFilePath);

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, localFilePath]() {
        handleDownloadReply(reply);
        QFile file(localFilePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
        }
        emit fileDownloaded(localFilePath);
    });
}

void FtpClient::uploadFile(const QString &localFilePath, const QString &remoteFilePath)
{
    QFile file(localFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open local file for uploading:" << localFilePath;
        return;
    }

    QUrl url = ftpUrl;
    url.setPath(remoteFilePath);

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->put(request, file.readAll());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit fileUploaded();
            qDebug() << "File uploaded successfully!";
        } else {
            qDebug() << "File upload failed:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void FtpClient::handleListReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QStringList fileList = QString(reply->readAll()).split("\n", Qt::SkipEmptyParts);
        emit directoryListed(fileList);
    } else {
        qDebug() << "Directory listing failed:" << reply->errorString();
    }
    reply->deleteLater();
}

void FtpClient::handleDownloadReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "File download failed:" << reply->errorString();
    }
    else {
        qDebug() << "File downloaded successfully!";
    }
    reply->deleteLater();
}
