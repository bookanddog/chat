#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T17:15:03
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app
#CONFIG+=release

INCLUDEPATH+="D:\PostgreSQL\9.4\include"
LIBS+="D:\PostgreSQL\9.4\lib\libpq.lib"

SOURCES += main.cpp\
        mainwindow.cpp \
    tcpserver.cpp \
    tcpconthread.cpp \
    sqldb.cpp

HEADERS  += mainwindow.h \
    tcpserver.h \
    tcpconthread.h \
    sqldb.h \
    user.h \
    userinfo.h \
    userfriend.h

FORMS    += mainwindow.ui
