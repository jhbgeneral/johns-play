#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOne_clicked()
{
    qDebug() << "  ui->lineEdit_1 =" << ui->lineEdit_1->text();
}

void MainWindow::on_btnTwo_clicked()
{
    qDebug() << "  ui->lineEdit_2 =" << ui->lineEdit_2->text();
}


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

// bool MainWindow::eventFilter(QObject *obj, QEvent *e)
// {
//     // Don't be flooded by mouse move events
//     if ((allowKeys == false) && (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease)) {
//         qDebug() << "allowKeys == false, blocking mouse press and release events";
//         return true;
//     }
//
//     qDebug() << "MainWindow::eventFilter(): enter" << e->type() << obj->objectName();
//     bool b = QMainWindow::eventFilter(obj, e);
//     qDebug() << "MainWindow::eventFilter(): returned" << b;
//     return QMainWindow::eventFilter(obj, e);
// }

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
