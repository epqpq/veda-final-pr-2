#include "gstreamerclient.h"
#include <QDebug>

GstreamerClient::GstreamerClient(QWidget *parent)
    : QOpenGLWidget(parent), pipeline(nullptr), glSink(nullptr), bus(nullptr)
{
}

GstreamerClient::~GstreamerClient()
{
    qDebug() << "GstreamerClient delete";
    stopPipeline();
}

bool GstreamerClient::startPipeline()
{
    GError *error = nullptr;

    // GStreamer 초기화
    gst_init(nullptr, nullptr);

    // GStreamer 파이프라인 생성
    pipeline = gst_parse_launch(pipelineStr.toUtf8().constData(), &error);
    if (!pipeline) {
        qDebug() << "Failed to create pipeline, Error message:" << error->message;
        g_clear_error(&error);
        return false;
    }

    // GL Sink 설정
    glSink = gst_bin_get_by_interface(GST_BIN(pipeline), GST_TYPE_VIDEO_OVERLAY);
    if (!glSink) {
        qDebug() << "Failed to get glimagesink";
        gst_object_unref(pipeline);
        pipeline = nullptr;
        return false;
    }

    // Window ID 설정
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(glSink), winId());

    // 파이프라인 버스 가져오기
    bus = gst_element_get_bus(pipeline);
    if (bus) {
        gst_bus_add_watch(bus, (GstBusFunc)onBusMessage, this);
    }

    // 파이프라인 시작
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    return true;
}

void GstreamerClient::stopPipeline()
{
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline = nullptr;
    }
    if (glSink) {
        gst_object_unref(glSink);
        glSink = nullptr;
    }
    if (bus) {
        gst_object_unref(bus);
        bus = nullptr;
    }
}

void GstreamerClient::initializeGL()
{
    // OpenGL 초기화
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void GstreamerClient::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GstreamerClient::setGstreamerClient(const QString& pipeline, const QString& id)
{
    pipelineStr = pipeline;
    clientID = id;
}

// GStreamer 버스 메시지 처리 콜백
bool GstreamerClient::onBusMessage(GstBus* bus, GstMessage* message, gpointer user_data)
{
    GstreamerClient* client = static_cast<GstreamerClient*>(user_data);

    switch (GST_MESSAGE_TYPE(message)) {
    case GST_MESSAGE_ERROR: {
        GError *err = nullptr;
        gchar *debug = nullptr;
        gst_message_parse_error(message, &err, &debug);
        qDebug() << "GStreamer error:" << err->message;
        g_error_free(err);
        g_free(debug);
        emit client->streamingStopped("Error occurred in GStreamer pipeline.");
        break;
    }
    case GST_MESSAGE_EOS: {
        qDebug() << "GStreamer pipeline reached end of stream.";
        emit client->streamingStopped("End of stream reached.");
        break;
    }
    default:
        break;
    }
    return TRUE;
}

