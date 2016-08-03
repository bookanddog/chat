#include "tcpserver.h"
#include "tcpconthread.h"
#include <QMessageBox>

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{

}

void TcpServer::incomingConnection(int socketDescriptor)
{
    //QMessageBox::critical(NULL, QStringLiteral("提示"), QStringLiteral("开启新线程没"));
    TcpConThread *thread = new TcpConThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
