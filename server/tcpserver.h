#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QStringList>
#include <QtNetwork/QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT

public:
    TcpServer(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);

private:

};

#endif // TCPSERVER

