#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QtGui>
#include "server.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    Server server;
    void resetHall();
};

#endif // MAINWINDOWS_H
