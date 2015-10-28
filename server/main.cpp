#include <QtCore>
#include <QtGui>
#include "mainwindow.h"
//#include "db.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForCStrings(codec);

    //if (!createConnection())
    //    return 1;

    MainWindow mainwindow;
	mainwindow.show();

	return app.exec();
}
