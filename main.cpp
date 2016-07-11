#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Application with a main window to experiment
    // with processEvents() operations

    QApplication app(argc, argv);

    MainWindow mainWin;

//    app.installEventFilter(&mainWin);

    mainWin.show();

    return app.exec();
}
