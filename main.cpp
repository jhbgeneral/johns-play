#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Application with a main window to experiment
    // with Input Method Editor (IME) operations

    QApplication app(argc, argv);

    MainWindow mainWin;

    mainWin.show();

    return app.exec();
}
