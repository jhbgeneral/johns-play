#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

class QApplication;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnDoStuff_clicked();
    void on_btnOne_clicked();
    void on_btnTwo_clicked();

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent * e);
    bool event(QEvent *event);
};

#endif // MAINWINDOW_H
