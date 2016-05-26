#include <QApplication>
#include <QLabel>

extern void listPrinters();

int main( /* int argc, char *argv[] */ )
{
    listPrinters();

#if 0
    // Quicky Hello GUI app
    QApplication app(argc, argv);

    QLabel label ("Hello, QT World");
    label.show ();

    return app.exec();
#endif
}
