#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    allowKeys(true)
{
    ui->setupUi(this);

//    ui->btnDoStuff->installEventFilter(this);
//    ui->btnOne->installEventFilter(this);
//    ui->btnTwo->installEventFilter(this);
    this->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Experimented with simple Qt app on the Linux VM -- to disable the "Start"
// button before a sleep(), and enable "Start" after the sleep, and see if
// processEvents() helps anything.  The short answer is that I found a sequence
// that works!  On the VM.  The same app fails when run on the VS-100 target.

// btnDoStuff is the "Start" button, and btnOne and btnTwo are for further
// experimenting.
//	• btnDoStuff appears properly and behaves properly (as desired)
//		○ 59: is disabled immediately,
//		○ 61: its appearance is updated to show disabled during processEvents()
//		○ 65: is still disabled during the 2nd processEvents() so presses
//              during the sleep() are discarded
//		○ 67: is enabled just when the handler ends
//	• btnOne appears properly but its behavior is NOT as desired
//		○ 60: is disabled immediately,
//		○ 61: its appearance is updated to show disabled during processEvents()
//		○ 64: is enabled after the sleep, but before processEvents()
//		○ 65: since it is enabled during the 2nd processEvents() presses during
//              the sleep() are processed
//	• btnTwo appears incorrectly but behaves properly (as desired)
//		○ 62: is disabled after processEvents(), so does NOT get visually
//              updated, still appears enabled
//		○ 65: I believe processEvents() handles events in this order:
//			§ becomes disabled
//			§ processes (discards) presses queued during the sleep, so behavior
//              is as desired
//		○ 66: is enabled just when the handler ends
// So, the location of processEvents() is critical to both the appearance and
// behavior of the buttons.
//
// Great!  Let's build and run the same app on the VS-100 target.
// NFG!  No Good!  All button presses are acted upon regardless of where the
// processEvents() is placed relative to the buttons' being enabled or disabled.
// But the buttons' appearances were exactly as above.  Note, too, that the test
// app was also the window manager, i.e., invoked as johns-test -qws.
//
// !!! When vsd-power.sh was running on the target, it was the QWS Server, and
// this test app then worked as expected, as it did on the Linux VM!


void MainWindow::on_btnDoStuff_clicked()
{
    qDebug() << "on_btnDoStuff_clicked() entering";
//    if (allowKeys == false) {
//        qDebug() << "    ... allowKeys == FALSE, returning now";
//        return;
//    }
    qDebug() << "Setting allowKeys to false and starting sleep(5)";
    setEnabled(false);
    sleep(1);
    allowKeys = false;
//    ui->btnDoStuff->setEnabled(false);
//    ui->btnOne->setEnabled(false);
    qApp->processEvents();
//    ui->btnTwo->setEnabled(false);
    sleep(5);
//    ui->btnOne->setEnabled(true);
    qApp->processEvents();
//    ui->btnTwo->setEnabled(true);
//    ui->btnDoStuff->setEnabled(true);
    qDebug() << "Sleep() done and resetting allowKeys to true";
    allowKeys = true;
    setEnabled(true);
    qDebug() << "on_btnDoStuff_clicked() returning";
}

void MainWindow::on_btnOne_clicked()
{
    qDebug() << "on_btnOne_clicked() entering";
//    if (allowKeys == false) {
//        qDebug() << "    ... allowKeys == FALSE, returning now";
//        return;
//    }
    qDebug() << "on_btnOne_clicked() returning";
}

void MainWindow::on_btnTwo_clicked()
{
    qDebug() << "on_btnTwo_clicked() entering";
//    if (allowKeys == false) {
//        qDebug() << "    ... allowKeys == FALSE, returning now";
//        return;
//    }
    qDebug() << "on_btnTwo_clicked() returning";
}


// //
// // This overrides the QMainWindow's paintEvent(), method #1, on page 174,
// // and then calls the parent's paintEvent() to do the real paint
// //
// void MainWindow::paintEvent(QPaintEvent *e)
// {
//     qDebug() << "MainWindow::paintEvent(): enter";
//     QMainWindow::paintEvent(e);
//     qDebug("MainWindow::paintEvent(): return");
// }


// //
// // This overrides the QMainWindow's event(), method #2, on page 174,
// // and then calls the parent's event() to do the real work
// //
// bool MainWindow::event(QEvent *e)
// {
// //    // Don't be flooded by mouse move events
// //    if (e->type() == QEvent::MouseMove || e->type() == QEvent::HoverEnter ||
// //            e->type() == QEvent::HoverLeave || e->type() == QEvent::HoverMove) {
// //        return false;
// //    }
//
//     qDebug() << "  MainWindow::event(): enter" << e->type();
//     if (allowKeys == false) {
//         qDebug() << "    ... allowKeys == FALSE, returning true now";
//         return true;
//     }
//     bool b = QMainWindow::event(e);
//     qDebug() << "  MainWindow::event(): returned" << b;
//     return b;
// }


//
// This is an event filter to support method 3, on page 174.  In this case, this
// event filter is installed for individual objects (buttons) in the ctor.
//

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    // Don't be flooded by mouse move events
    if ((allowKeys == false) && (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease)) {
        qDebug() << "allowKeys == false, blocking mouse press and release events";
        return true;
    }

//    qDebug() << "MainWindow::eventFilter(): enter" << e->type() << obj->objectName();
//    bool b = QMainWindow::eventFilter(obj, e);
//    qDebug() << "MainWindow::eventFilter(): returned" << b;
    return QMainWindow::eventFilter(obj, e);
}

//
// The event filter used above, for method 3, is also used here, for method 4,
// on page 174, by installing the filter on the QApplication object in the ctor
//


//
// NONE of methods 1-4, above, intercepts button clicks; NO events are shown.
// Using method 4, installing an event filter on MainWindow (oops, method 4
// should install an event filter on the QApplication object, so I guess this
// is really just another implementation of method 3) and returning true (to
// indicate the event was handled) made no difference.  Back to main.cpp to
// install the event filter on the QApplication.
//

// TODO:  5, Subclass QApplication and reimplement notify()
