#include <myqapplication.h>
#include <QLabel>

int main(int argc, char *argv[])
{
    MyQApplication app(argc, argv);

    QLabel lbl;
    lbl.setText("Hello, QT World!");
    lbl.setObjectName("Hello Label");
    lbl.show();

    return app.exec();
}
