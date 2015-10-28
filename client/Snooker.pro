#-------------------------------------------------
#
# Project created by QtCreator 2013-03-22T15:14:25
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = Snooker
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    mainwindow.cpp \
    gotoplay.cpp \
    ball.cpp \
    connectServer.cpp

HEADERS  += login.h \
    mainwindow.h \
    gotoplay.h \
    ball.h \
    Typedefine.h \
    connectServer.h \
    global.h

FORMS    += login.ui \
    mainwindow.ui \
    gotoplay.ui

RESOURCES += \
    MyResources.qrc
	
RC_FILE = myapp.rc
