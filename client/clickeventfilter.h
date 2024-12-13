#include <QObject>
#include <QEvent>
#include <QMouseEvent>

class ClickEventFilter : public QObject {
    Q_OBJECT

public:
    explicit ClickEventFilter(QObject* parent = nullptr) : QObject(parent) {}

signals:
    void clicked();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override {
        if (event->type() == QEvent::MouseButtonPress) {
            auto mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                emit clicked();
                return true;
            }
        }
        return QObject::eventFilter(obj, event);
    }
};
