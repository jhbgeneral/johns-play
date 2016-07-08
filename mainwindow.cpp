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
    qDebug("Begin sleep(5)");
    ui->btnDoStuff->setEnabled(false);
    ui->btnOne->setEnabled(false);
    qApp->processEvents();
    ui->btnTwo->setEnabled(false);
    sleep(5);
    ui->btnOne->setEnabled(true);
    qApp->processEvents();
    ui->btnTwo->setEnabled(true);
    ui->btnDoStuff->setEnabled(true);
    qDebug("End sleep()");
}

void MainWindow::on_btnOne_clicked()
{
    qDebug("on_btnOne_clicked");
}

void MainWindow::on_btnTwo_clicked()
{
    qDebug("on_btnTwo_clicked");
}

//
// This overrides the QMainWindow's paintEvent(), method #1, on page 174,
// and then calls the parent's paintEvent() to do the real paint
//
void MainWindow::paintEvent(QPaintEvent *e)
{
    qDebug("MainWindow::paintEvent(): enter");
    QMainWindow::paintEvent(e);
    qDebug("MainWindow::paintEvent(): return");
}

//
// This overrides the QMainWindow's event(), method #2, on page 174,
// and then calls the parent's event() to do the real work
//
bool MainWindow::event(QEvent *e)
{
    qDebug("MainWindow::event(): enter");
    bool b = QMainWindow::event(e);
    qDebug() << "MainWindow::event(): returned" << b;
}

// TODO:  3, Install event filter for single object

// TODO:  4, Install event filter on the QApplication object

// TODO:  5, Subclass QApplication and reimplement notify()
