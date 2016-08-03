#include "dlgload.h"
#include "ui_dlgload.h"

//得有一个文件放置登录设置和信息，后面添加
DlgLoad::DlgLoad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLoad)
{
    ui->setupUi(this);

    ui->lineEditCount->clear();
    ui->lineEditPwd->clear();

    this->setWindowTitle("loading");
    m_count.clear();
    m_pwd.clear();
    m_tcpSocket = new QTcpSocket(this);
    m_serverIP = "127.0.0.1";
    m_serverPort = "6868";

    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(on_ready_Read()));
}

DlgLoad::~DlgLoad()
{
    delete ui;
}

//设置一个超时相应，不然没有反应会一直在登录中
void DlgLoad::on_pushButtonLoad_clicked()
{
    ui->pushButtonLoad->setText("Loading...");
    m_count = ui->lineEditCount->text().trimmed();
    m_pwd = ui->lineEditPwd->text().trimmed();

    m_tcpSocket->abort();
    //m_tcpSocket->connectToHost();
    //按道理说用户是不知道地址的，但是可以手动填写。设置两个成员变量，可以更改。
    m_tcpSocket->connectToHost(QHostAddress(m_serverIP), (quint16)m_serverPort.toUInt());

    QString msg = "LOGIN";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << (quint16)0 << msg << m_count << m_pwd;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);

}

void DlgLoad::on_ready_Read()
{
    //QMessageBox::critical(NULL, QStringLiteral("提示"), QStringLiteral("连接发出去没"));
    QByteArray block = m_tcpSocket->readAll();
    QDataStream in(&block, QIODevice::ReadOnly);
    quint16 dataGramSize;
    QString msg;
    in >> dataGramSize >> msg;

    if(msg == "COUNT_NOTEXIST")
    {     //提醒方式可以改一下,messagebox太不友好
        QMessageBox::warning(NULL, tr("提示"), tr("用户不存在！"));

    }
    else if(msg == "PWD_ERROR")
    {
         QMessageBox::warning(NULL, tr("提示"), tr("密码错误!"));
         ui->lineEditPwd->clear();
    }
    else if(msg == "LOGIN_ALREADY")
    {
         QMessageBox::warning(NULL, tr("提示"), tr("用户已登录！"));
    }
    else if(msg == "LOGIN_SUCCESS")
    {        //重载构造函数
        m_clientPort = m_tcpSocket->localPort();
        m_chatList = new ChatList(m_count, m_serverIP, m_serverPort, m_clientPort);
        m_chatList->setWindowTitle(tr("chat"));
        m_chatList->show();
        this->close();
    }
}
