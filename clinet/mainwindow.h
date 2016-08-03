#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QString count, QString ip, QString port, QUdpSocket *udpScoket);
    ~MainWindow();

    void displayText(QString count, QString saying);


private slots:
    //void connectToServer();
    void sendMessage();
    //void processPendingDatagrams();


private:
    Ui::MainWindow *ui;
    QUdpSocket     *m_udpSocket;
    QString         m_serverIP;
    QString         m_serverPort;

    QString         m_count;
    //QTcpSocket      m_tcpSocket;

};

#endif // MAINWINDOW_H
