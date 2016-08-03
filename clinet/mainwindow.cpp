#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //关于udp这两句放在哪里比较好？？？？？？？？
    //if(!m_udpSocket.bind(QHostAddress(m_serverIP)), (quint16)m_serverPort)
   // {
       // QMessageBox::critical(NULL, QStringLiteral("提示"), QStringLiteral("udp绑定失败：%1.").arg(m_udpSocket.errorString()));
    //}
   //connect(&m_udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    //待添加???????????????????

    //connect(ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(ui->pushButtonSend, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

MainWindow::MainWindow(QString count, QString ip, QString port, QUdpSocket *udpScoket) : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_count = count;
    this->m_serverIP = ip;
    this->m_serverPort = port;
    this->m_udpSocket = udpScoket;
    connect(ui->pushButtonSend, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::connectToServer()
{
    m_tcpSocket.connectToHost(QHostAddress::LocalHost, 6868);

}
*/
void MainWindow::sendMessage()
{
    QByteArray blockToSend;
    QDataStream toSend(&blockToSend, QIODevice::WriteOnly);
    toSend.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    QString msg = "CHAT";
    toSend << (quint16) 0 << msg << m_count << this->windowTitle() << ui->textEditSend->toPlainText();
    //这两句是为了覆盖最开始写的datagramsize的0？好像还是没有用，意义何在
    toSend.device()->seek(0);
    toSend << (qint16) (blockToSend.size() - sizeof(quint16));

    if(!m_udpSocket->writeDatagram(blockToSend.data(), blockToSend.size(), QHostAddress(m_serverIP), (quint16)m_serverPort.toUInt()))
        QMessageBox::warning(NULL, "message sending", "error");

    ui->textBrowserChartShow->append(ui->textEditSend->toPlainText());
    //ui->textBrowserChartShow->setText("\n");
    ui->textEditSend->clear();
}

/*
void MainWindow::processPendingDatagrams()
{
    while(m_udpSocket.hasPendingDatagrams())
    {
        QByteArray block;
        block.resize(m_udpSocket.pendingDatagramSize());
        if(m_udpSocket.readDatagram(block.data(), block.size()) == -1)
        {
            continue;
        }
        QDataStream in(&block, QIODevice::ReadOnly);
        quint16  dataGramSize;
        QString msg;

        in >> dataGramSize >> msg;
        if( msg == "SERVER_INFO")
        {
            //QString toId,fromId,fromName,toIp;
            //in >> fromId >> toId >> buffer
            //真正实现是用户对用户的通信
            QString buffer;
            in >> buffer;
            //用户对用户通信时不显示在服务器端
            ui->textBrowserChartShow->append(buffer);

        }
    }

}
*/

void MainWindow::displayText(QString count, QString saying)
{
     ui->textBrowserChartShow->append(count + ":" + saying);
}
