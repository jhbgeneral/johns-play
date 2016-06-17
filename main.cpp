#include <QApplication>
#include <QLabel>
#include <QDebug>

// extern void listPrinters();
extern void testIterators();

int main( /* int argc, char *argv[] */ )
{
    testIterators();

    // listPrinters();
#if 0
    // Quicky Hello GUI app
    QApplication app(argc, argv);

    QLabel label ("Hello, QT World");
    label.show ();

    return app.exec();
#endif
}
