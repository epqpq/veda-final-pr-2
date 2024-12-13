#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include "ftpclient.h"

class FtpMonitor : public QObject {
    Q_OBJECT
public:
    explicit FtpMonitor(QObject *parent = nullptr) : QObject(parent), client(new FtpClient(this))
    {
        connect(client, &FtpClient::directoryListed, this, &FtpMonitor::onDirectoryListed);
    }

    void start(const QString &ftpUrl, const QString &username, const QString &password, const QString &remoteDirectory, int intervalMs = 5000)
    {
        this->remoteDirectory = remoteDirectory;
        // FTP 서버 연결
        client->connectServer(ftpUrl, username, password);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &FtpMonitor::pollDirectory);
        timer->start(intervalMs);
    }

private slots:
    void pollDirectory() {
        client->listDirectory(remoteDirectory);
    }

    void onDirectoryListed(const QStringList &fileList) {
        // 이전 목록이 존재한다면 비교
        if (!prevFileList.isEmpty()) {
            for (const QString &file : fileList) {
                // 이전에 없던 파일은 새로운/변경된 파일로 간주
                if (!prevFileList.contains(file)) {
                    qDebug() << "New or updated file detected:" << file;

                    // 해당 파일 다운로드 (예: downloads 폴더에 저장)
                    QString localFilePath = "downloads/" + file.trimmed();
                    client->downloadFile(remoteDirectory + "/" + file.trimmed(), localFilePath);
                }
            }
        }
        // 현재 목록을 다음 비교를 위해 저장
        prevFileList = fileList;
    }

private:
    FtpClient *client;
    QTimer *timer;
    QStringList prevFileList;
    QString remoteDirectory;
};

// #include "main.moc" // Q_OBJECT 매크로 사용 시 필요 (또는 빌드 설정에서 자동생성)

// int main(int argc, char *argv[]) {
//     QCoreApplication app(argc, argv);

//     // 사용 예제
//     FtpMonitor monitor;
//     monitor.start("ftp://example.com", "username", "password", "/path/to/watch", 5000);

//     return app.exec();
// }
