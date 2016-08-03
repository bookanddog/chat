#ifndef TCPCONTHREAD_H
#define TCPCONTHREAD_H

#include <QThread>
#include <QtNetwork/QTcpSocket>
#include "sqldb.h"

class TcpConThread : public QThread
{
    Q_OBJECT

public :
    TcpConThread(int socketDescriptor, QObject *parent);
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int        m_socketDescriptor;
    QTcpSocket *m_tcpSocket;
    //后期加入数据库
    SqlDB      *m_db;
    /**/

private slots:
    void on_Ready_Read();
};

#endif // TCPCONTHREAD_H

