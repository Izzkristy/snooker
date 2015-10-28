#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    
public:
    explicit Login(QWidget *parent = 0);
    ~Login();

signals:
    void loginsuccess();

private slots:
    void checkLogin();
    void sendLogin();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
