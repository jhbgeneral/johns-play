#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Application with a main window to experiment
    // with QWSServer and QWSClient operations

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
