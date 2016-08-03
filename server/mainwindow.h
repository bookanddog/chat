#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include "tcpserver.h"
#include "sqldb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //待补充

private slots:
    void on_pushButtonSend_clicked();
    void on_pushButtonListen_clicked();
    void on_read_Datagrams();

private:
    void processDatagram(QByteArray block);

private:
    Ui::MainWindow *ui;
    QUdpSocket     *m_udpSocket;
    TcpServer       m_server;
    QString         m_serverIp;
    QString         m_serverPort;
    QHostAddress    m_senderIp;
    quint16         m_senderPort;
    SqlDB          *m_db;

};

#endif // MAINWINDOW_H
