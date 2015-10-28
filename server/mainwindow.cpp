#include "mainwindow.h"
#include <QtGui>
#include <QtNetwork>
#include <stdlib.h>
#include "desk.h"

struct Player player[PLAYERNUM];
int onlineNum = 0;
//ClientSocket *socket[MAXTHREADNUM];

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    statusLabel = new QLabel;
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    if (!server.listen(QHostAddress::Any, 7962))
    {
        QMessageBox::critical(this, tr("Threaded Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server.errorString()));
        close();
        return;
    }

    statusLabel->setText(QString("The server is running on port %1.\n")
                         .arg(server.serverPort()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle("Threaded 中文 Server");
    this->resetHall();
}

void MainWindow::resetHall()
{
    onlineNum = 0;
    for(int i=0;i<PLAYERNUM;i++)
    {
        player[i].id = 0;
        player[i].name = "";
        player[i].score = 0;
    }
}
