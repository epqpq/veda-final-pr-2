#ifndef _GSTREAMER_CLIENT_H_
#define _GSTREAMER_CLIENT_H_

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <gst/gst.h>
#include <gst/gl/gstglcontext.h>
#include <gst/video/videooverlay.h>

class GstreamerClient : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit GstreamerClient(QWidget *parent = nullptr);
    ~GstreamerClient() override;

    bool startPipeline();
    void stopPipeline();
    void setGstreamerClient(const QString& pipelineStr, const QString& id);

signals:
    void streamingStopped(const QString& reason); // 스트리밍 중단 알림 시그널

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    static bool onBusMessage(GstBus* bus, GstMessage* message, gpointer user_data);

    GstElement* pipeline;       // GStreamer pipeline 객체
    GstElement* glSink;         // GStreamer GLImageSink
    GstBus* bus;                // GStreamer 버스
    QString pipelineStr;        // 파이프라인 문자열
    QString clientID;           // GStreamer 클라이언트 ID
};

#endif // _GSTREAMER_CLIENT_H_
