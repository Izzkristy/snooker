#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include "gotoplay.h"
//#include "login.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void hallshow();

private slots:
    void on_Location1_clicked();
    void on_Location2_clicked();
    void on_Location3_clicked();
    void on_Location4_clicked();
    void on_Location5_clicked();
    void on_Location6_clicked();
    void on_Location7_clicked();
    void on_Location8_clicked();
    void on_Location9_clicked();
    void on_Location10_clicked();
    void on_Location11_clicked();
    void on_Location12_clicked();
    void on_Location13_clicked();
    void on_Location14_clicked();
    void on_Location15_clicked();
    void on_Location16_clicked();
    void on_Location17_clicked();
    void on_Location18_clicked();

    void on_action_triggered();
    void on_action_2_triggered();

    void updateHall();
    void setHallInfo();
    void startPlay(quint8);
    void quitPlay();

private:
    Ui::MainWindow *ui;
    void resetGlobal();
    void setDesk();
    //QTimer updatetimer;
    Gotoplay *dlg;
    //Login login;
};

#endif // MAINWINDOW_H
