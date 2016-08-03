#include "mainwindow.h"
#include <QApplication>
#include "dlgload.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DlgLoad *load = new DlgLoad;
    load->show();

    //MainWindow w;
    //w.show();

    return a.exec();
}
