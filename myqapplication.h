#ifndef MYQAPPLICATION_H
#define MYQAPPLICATION_H

#include <QApplication>

class MyQApplication : public QApplication
{
    Q_OBJECT
public:
    explicit MyQApplication(int argc, char *argv[]);
    virtual bool notify(QObject *obj, QEvent *evt);

    int allowKeys;

signals:
    
public slots:

};

#endif // MYQAPPLICATION_H
