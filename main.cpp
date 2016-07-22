#include <QApplication>
#include "myqapplication.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    MyQApplication app(argc, argv);

    MainWindow mainWin;

    mainWin.show();

    return app.exec();
}
