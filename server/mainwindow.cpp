#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
//#include "tcpserver.h"
//#include "sqldb.h"
//套接字消息中的dataGramSize总为0，目前并没有看出来什么用
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("chartServer");
    ui->pushButtonListen->setText(QStringLiteral("开始监听"));

    m_serverIp.clear();
    m_serverPort.clear();
    m_db = new SqlDB;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonListen_clicked()
{
    //m_serverIp.clear();
    //m_senderPort.clear();
    //设置主机IP地址和端口号,在主机上可能有多个ip，以后添加界面手动设置的功能

    m_serverIp = "127.0.0.1";
    m_serverPort = "6868";
    if(ui->pushButtonListen->text() == QStringLiteral("开始监听"))
    {
        if(!m_server.listen(QHostAddress(m_serverIp), (quint16)m_serverPort.toUInt()))
        {
          QMessageBox::critical(NULL, QStringLiteral("提示"), QStringLiteral("监听失败：%1.").arg(m_server.errorString()));
        }
        else
        {
            m_udpSocket = new QUdpSocket(this);
            if(!m_udpSocket->bind(QHostAddress(m_serverIp), (quint16)m_serverPort.toUInt()))
            {
                QMessageBox::critical(NULL, QStringLiteral("提示"), QStringLiteral("udp绑定失败：%1.").arg(m_udpSocket->errorString()));
            }
            connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(on_read_Datagrams()));

            ui->pushButtonListen->setText(QStringLiteral("断开监听"));
            //

        }
    }
    else if(ui->pushButtonListen->text() == QStringLiteral("断开监听"))
    {
        m_server.close();
        m_udpSocket->close();
        ui->pushButtonListen->setText(QStringLiteral("开始监听"));
        //
    }
}

void MainWindow::on_read_Datagrams()
{
    while(m_udpSocket->hasPendingDatagrams())
    {
        QByteArray block;
        block.resize(m_udpSocket->pendingDatagramSize());
        if(m_udpSocket->readDatagram(block.data(), block.size(), &m_senderIp, &m_senderPort) == -1)
            continue;

        processDatagram(block);
    }
}

void MainWindow::processDatagram(QByteArray block)
{
    QDataStream in(&block, QIODevice::ReadOnly);
    quint16  dataGramSize;
    QString msg;
    in >> dataGramSize >> msg;
    qDebug()<< "Available drivers:"<<msg;
    if( msg == "CHAT")
    {
        //QString toId,fromId,fromName,toIp;
        //in >> fromId >> toId >> buffer
        //真正实现是用户对用户的通信
        QString fromcount, tocount;
        QString buffer;
        in >> fromcount >> tocount >> buffer;
        //用户对用户通信时不显示在服务器端
        ui->textBrowserChert->append(buffer);
        QByteArray blockToSend;
        QDataStream toSend(&blockToSend, QIODevice::WriteOnly);
        toSend.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        QString msg = "CHAT";
        toSend << (quint16) 0 << msg <<  fromcount << buffer;
        //这两句是为了覆盖最开始写的datagramsize的0？好像还是没有用，意义何在
        toSend.device()->seek(0);
        toSend << (qint16) (blockToSend.size() - sizeof(quint16));

        QString ip, port;
        m_db->getUserNet(tocount, ip, port);
        qDebug()<< fromcount << tocount << ip << port;
        if(!m_udpSocket->writeDatagram(blockToSend.data(), blockToSend.size(), QHostAddress(ip), (quint16)port.toUInt()))
            QMessageBox::warning(NULL, "message sending", "error");
    }
    //因为是用户对用户的通信，所以以后会有一个转发的过程
    /**/

    //新连接到来后还需要给用户他自己的信息,可以在过程tcp传输
    //值得再考虑考虑
    else if( msg == "NEW_CONN")
    {
        QString count;
        in >> count;
        m_db->getUserFriends(count);
        m_db->updateUsernet(count, m_senderIp.toString(), QString::number(m_senderPort));
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        QString msg = "FRIENDS";
        out << (quint16)0 << msg << m_db->m_userFriends.m_countArry << msg << m_db->m_userFriends.m_groupArry << msg << m_db->m_userFriends.m_nowfriendArry << msg << m_db->m_userFriends.m_nicknameArry << msg << m_db->m_userFriends.m_stateArry << msg << m_db->m_userFriends.m_mottoArry;

        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16) );
        m_udpSocket->writeDatagram(block.data(), block.size(), m_senderIp, m_senderPort);

        //m_tcpSocket->write(block);
    }

}

void MainWindow::on_pushButtonSend_clicked()
{
    QByteArray blockToSend;
    QDataStream toSend(&blockToSend, QIODevice::WriteOnly);
    toSend.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    QString msg = "SERVER_INFO";
    toSend << (quint16) 0 << msg << ui->textEditSend->toPlainText();
    //这两句是为了覆盖最开始写的datagramsize的0？好像还是没有用，意义何在
    toSend.device()->seek(0);
    toSend << (qint16) (blockToSend.size() - sizeof(quint16));

    if(!m_udpSocket->writeDatagram(blockToSend.data(), blockToSend.size(), QHostAddress(m_senderIp),(quint16)m_serverPort.toUInt()))
        QMessageBox::warning(NULL, "message sending", "error");
    //
    ui->textBrowserChert->append(ui->textEditSend->toPlainText());
    //ui->textBrowserChert->append("\n");
    ui->textEditSend->clear();


}
