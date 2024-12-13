#ifndef _GSTREAMER_CLIENT_THREAD_H_
#define _GSTREAMER_CLIENT_THREAD_H_

#include <QThread>
#include <QString>
#include "gstreamerclient.h"

class GstreamerClientThread : public QThread
{
    Q_OBJECT
public:
    explicit GstreamerClientThread(GstreamerClient* client, QObject* parent = nullptr);
    ~GstreamerClientThread();
protected:
    void run() override;
private:
    GstreamerClient* gstreamerClient;
};

#endif // GSTREAMERCLIENTTHREAD_H
