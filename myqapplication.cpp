#include "myqapplication.h"
#include "QDebug"
#include "QDateTime"

MyQApplication::MyQApplication(int argc, char *argv[]) :
    QApplication(argc, argv),
    allowKeys(true)
{
}

bool MyQApplication::notify(QObject *obj, QEvent *evt)
{
    // See if this is something we should skip
    if (allowKeys == false)
    {
        switch (evt->type())
        {
            case QEvent::MouseButtonDblClick:
                qDebug() << "allowKeys == false, skipping MouseButtonDblClick";
                return true;
            case QEvent::MouseButtonPress:
                qDebug() << "allowKeys == false, skipping MouseButtonPress";
                return true;
            case QEvent::MouseButtonRelease:
                qDebug() << "allowKeys == false, skipping MouseButtonRelease";
                return true;
            case QEvent::KeyPress:
                qDebug() << "allowKeys == false, skipping KeyPress";
                return true;
            case QEvent::KeyRelease:
                qDebug() << "allowKeys == false, skipping KeyRelease";
                return true;
            default:
                break;
        }
    }


    // Display event type, then process
    QString evtStr;
    switch (evt->type())
    {
        // Display event type, then process
        // Commented-out events will also not be debug-printed
//        case QEvent::ActivationChange: evtStr = "ActivationChange"; break;
//        case QEvent::ChildAdded: evtStr = "ChildAdded"; break;
//        case QEvent::ChildRemoved: evtStr = "ChildRemoved"; break;
//        case QEvent::Close: evtStr = "Close"; break;
//        case QEvent::Create: evtStr = "Create"; break;
//        case QEvent::CursorChange: evtStr = "CursorChange"; break;
//        case QEvent::DeferredDelete: evtStr = "DeferredDelete"; break;
//        case QEvent::Destroy: evtStr = "Destroy"; break;
        case QEvent::Enter: evtStr = "Enter"; break;
        case QEvent::FocusIn: evtStr = "FocusIn"; break;
        case QEvent::FocusOut: evtStr = "FocusOut"; break;
        case QEvent::KeyPress: evtStr = "KeyPress"; break;
        case QEvent::KeyRelease: evtStr = "KeyRelease"; break;
//        case QEvent::LayoutRequest: evtStr = "LayoutRequest"; break;
        case QEvent::Leave: evtStr = "Leave"; break;
        case QEvent::MouseButtonPress: evtStr = "MouseButtonPress"; break;
        case QEvent::MouseButtonRelease: evtStr = "MouseButtonRelease"; break;
        case QEvent::MouseButtonDblClick: evtStr = "MouseButtonDblClick"; break;
//        case QEvent::MouseMove: evtStr = "MouseMove"; break;
//        case QEvent::Paint: evtStr = "Paint"; break;
//        case QEvent::Polish: evtStr = "Polish"; break;
//        case QEvent::PolishRequest: evtStr = "PolishRequest"; break;
//        case QEvent::ShortcutOverride: evtStr = "ShortcutOverride"; break;
//        case QEvent::SockAct: evtStr = "SockAct"; break;
//        case QEvent::Timer: evtStr = "Timer"; break;
//        case QEvent::UpdateRequest: evtStr = "UpdateRequest"; break;
//        case QEvent::WindowActivate: evtStr = "WindowActivate"; break;
//        case QEvent::WindowDeactivate: evtStr = "WindowDeactivate"; break;
//        case QEvent::WinIdChange: evtStr = "WinIdChange"; break;

        // Comment-out the following line to see ALL events
        default: evtStr = "noprint"; break;
    }


    if (evtStr.isEmpty())
    {
        // No name specified, output the type number
        qDebug() << QString("%1  %2\t%3").arg(QTime::currentTime().toString()).arg(evt->type()).arg(obj->objectName());
    }
    else if (evtStr != "noprint")
    {
        // A name is specified, so use it
        qDebug() << QString("%1  %2\t%3").arg(QTime::currentTime().toString()).arg(evtStr).arg(obj->objectName());
    }
    else
    {
        // The string is explicitly flagged for no debug output
        ;
    }
    return QApplication::notify(obj, evt);
}
