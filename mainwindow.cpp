#include "myqapplication.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

extern int allowKeys;

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


void MainWindow::on_btnDoStuff_clicked()
{
    MyQApplication *myApp = qobject_cast <MyQApplication *> (qApp);
    qDebug() << "on_btnDoStuff_clicked() entering";

    // Starting a long-running operation, set a flag in notify() to block keys
    myApp->allowKeys = false;

    // Start the long-running operation, keys & events will be queued
    sleep(5);

    // Clear out key and mouse events accumulated during the sleep
    QApplication::processEvents();

    // Re-enable normal processing
    myApp->allowKeys = true;

    qDebug() << "on_btnDoStuff_clicked() returning";
}

void MainWindow::on_btnOne_clicked()
{
    qDebug() << "on_btnOne_clicked()";
}

void MainWindow::on_btnTwo_clicked()
{
    qDebug() << "on_btnTwo_clicked()";
}
