#include "gstreamerclientthread.h"
#include <QMetaObject>
#include <QDebug>

GstreamerClientThread::GstreamerClientThread(GstreamerClient* client, QObject* parent)
    : QThread(parent), gstreamerClient(client)
{

}

GstreamerClientThread::~GstreamerClientThread()
{
    qDebug() << "GstreamerClientThread delete";
    if (isRunning()) {
        requestInterruption();
        wait();
    }
}

void GstreamerClientThread::run() {
    if (!gstreamerClient) {
        qDebug() << "Gstreamer client is null";
        return;
    }

    // 파이프라인 시작
    bool success = false;
    QMetaObject::invokeMethod(gstreamerClient, [&]() {
        success = gstreamerClient->startPipeline();
    }, Qt::BlockingQueuedConnection);

    if (!success) {
        qDebug() << "Failed to start GStreamer pipeline in thread.";
        return;
    }

    // 스레드 실행 중 유지
    while (!isInterruptionRequested()) {
        QThread::msleep(100); // 주기적으로 대기
    }

    // 파이프라인 종료
    QMetaObject::invokeMethod(gstreamerClient, [&]() {
        gstreamerClient->stopPipeline();
    }, Qt::BlockingQueuedConnection);
}
