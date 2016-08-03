#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //乱码？

    MainWindow w;
    w.show();

    return a.exec();
}
