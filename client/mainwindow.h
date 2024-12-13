#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include <QMouseEvent>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QScreen>
#include <QScopedPointer>
#include <QFileDialog>
#include <QPushButton>
#include <QSlider>
#include <QTreeWidget>
#include <QVector>
#include <QListWidget>
#include <QCheckBox>
#include <utility>
#include <memory>
#include "client.h"
#include "selecteclientlist.h"
#include "ftpclient.h"

#define PIPELINE "tcpclientsrc host=%1 port=5000 ! tsdemux ! h264parse ! avdec_h264 ! videoconvert ! textoverlay text='%2' valignment=top halignment=left font-desc='Sans 24' ! video/x-raw,format=RGB ! glimagesink sync=false"
// #define PIPELINE    "rtspsrc location=rtsp://210.99.70.120:1935/live/cctv001.stream ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! textoverlay text='%1' valignment=top halignment=left font-desc='Sans 24'! video/x-raw,format=RGB ! glimagesink sync=false"

#define WIDGET_WIDTH    561
#define WIDGET_HEIGHT   401
#define ENLARGE_WIDTH  1000
#define ENLARGE_HEIGHT  750

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void appendLogMessage(const QString& message);
private:
    Ui::MainWindow* ui;
    Ui::SelecteClientList* selectClientList;
    std::unique_ptr<QDialog> selectDialog;
    std::unique_ptr<QMediaPlayer> videoPlayer;
    std::unique_ptr<FtpMonitor> monitor;
    std::vector<std::pair<std::shared_ptr<Client>, int>> clientList;

    bool enlargementFlag;
    bool videoPlayFlag;
    int widgetCount;
    int widgetPos[4][2] = {
        { 10 , 30  },
        { 590, 30  },
        { 10,  440 },
        { 590, 440 }
    };

private slots:
    void selectMenu(QTreeWidgetItem* item, int column);
    void registerClient();
    void deleteClient();
    void connectClient();
    bool addClient(QString& ip, QString& id);
    void selectClient(bool mode);
    void addClientTab(Client* client);
    void openClientWidget();
    void closeClientWidget();
    void enlargeClientWidget(Client* selectedClient);
    void setFilePath();
    void playVideo();
    void speedUpVideo();
    void speedDownVideo();
    void handleClientDisconnected(const QString& clientID); // gstreamer 연결이 종료되었을 경우 client 삭제
};

#endif // MAINWINDOW_H
