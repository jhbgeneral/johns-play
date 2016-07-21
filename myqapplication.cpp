#include "myqapplication.h"
#include "QDebug"
#include "QDateTime"

MyQApplication::MyQApplication(int argc, char *argv[]) :
    QApplication(argc, argv)
{
}

bool MyQApplication::notify(QObject *obj, QEvent *evt)
{
    if (evt->type() == QEvent::SockAct) return false;

    QString evtStr;
    switch (evt->type())
    {
//    case QEvent::SockAct:
//        return false;

    case QEvent::MouseMove: evtStr = "MouseMove"; break;
    case QEvent::MouseButtonPress: evtStr = "MouseButtonPress"; break;
    case QEvent::MouseButtonRelease: evtStr = "MouseButtonRelease"; break;
    case QEvent::MouseButtonDblClick: evtStr = "MouseButtonDblClick"; break;
    }

    if (evtStr.isEmpty()) {
        qDebug() << "Got it at" << QTime::currentTime().toString() << evt->type();
    } else {
        qDebug() << "Got it at" << QTime::currentTime().toString() << evtStr;
    }
    qDebug() << "    " << obj->objectName();
    return QApplication::notify(obj, evt);
}
