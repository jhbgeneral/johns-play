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


void MainWindow::on_btnDoStuff_clicked()
{
    qDebug() << "on_btnDoStuff_clicked() entering";
    sleep(5);
    qDebug() << "on_btnDoStuff_clicked() returning";
}

void MainWindow::on_btnOne_clicked()
{
    qDebug() << "on_btnOne_clicked() entering";
}

void MainWindow::on_btnTwo_clicked()
{
    qDebug() << "on_btnTwo_clicked() entering";
}
