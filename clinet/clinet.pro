#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T09:52:37
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clinet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dlgload.cpp \
    chatlist.cpp

HEADERS  += mainwindow.h \
    dlgload.h \
    chatlist.h \
    userinfo.h \
    user.h \
    userfriend.h

FORMS    += mainwindow.ui \
    dlgload.ui \
    chatlist.ui
