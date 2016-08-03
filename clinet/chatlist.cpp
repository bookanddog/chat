#include "chatlist.h"
#include "ui_chatlist.h"
#include <QDebug>

ChatList::ChatList(QString count, QString servip, QString servport, quint16 clientport, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatList)
{
    ui->setupUi(this);
    //m_chatform = NULL;//简陋的判断是否已经打开了聊天窗口

    this->m_serverIP = servip;
    this->m_serverPort = servport;
    m_userInfo.m_count = count;
    this->m_clientPort = clientport;
    ui->label_2->setText(m_userInfo.m_count);
    this->init();
    connect(ui->listWidgetUser, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_userListWidget_itemDoubleClicked(QListWidgetItem*)));
}

ChatList::~ChatList()
{
    delete ui;
}

void ChatList::init()
{
    m_udpSocket = new QUdpSocket(this);
    //这个端口会不会已经被占用,测试后看看,udp使用与tcp一样的端口号，考虑出现端口已经占用的问题
    if(!m_udpSocket->bind(m_clientPort))
        QMessageBox::critical(NULL, QStringLiteral("提示"), QStringLiteral("udp绑定失败：%1.").arg(m_udpSocket->errorString()));
    QString msg = "NEW_CONN";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << (quint16)0 << msg << m_userInfo.m_count;
    out.device()->seek(0);
    m_udpSocket->writeDatagram(block.data(), block.size(), QHostAddress(m_serverIP), (quint16)m_serverPort.toUInt());
    connect(this->m_udpSocket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
}

void ChatList::recvMsg()
{
    QByteArray block;
    QString msg;
    //QString count;
    //QString nickname;
    quint16 size;
    QHostAddress peerIP;
    quint16 peerPort;
    block.resize(m_udpSocket->pendingDatagramSize());
    this->m_udpSocket->readDatagram(block.data(), block.size(), &peerIP, &peerPort);
    QDataStream in(&block, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    in >> size >> msg;
    //以后慢慢写
    if(msg == "CHAT")
    {
        //QString peerName;
        QString peerCount;
        QString saying;
        in >>  peerCount >> saying;

        MainWindow *chat;
        if(m_chatfrom.contains(peerCount))
        {
            chat = m_chatfrom.value(peerCount);
        }
        else {
            chat = new MainWindow(m_userInfo.m_count, m_serverIP, m_serverPort, this->m_udpSocket);
            chat->setWindowTitle(peerCount);
            m_chatfrom.insert(peerCount, chat);
        }
        chat->show();
        chat->displayText(peerCount, saying);
    }
    //以后继续改,界面问题
    if(msg == "FRIENDS")
    {
        //QString name;
        //QString count;
        in >> m_userFriends.m_countArry >> m_userFriends.m_groupArry >> m_userFriends.m_nowfriendArry >> m_userFriends.m_nicknameArry >> m_userFriends.m_stateArry >> m_userFriends.m_mottoArry ;//>> name;
        //count.append("[" + name + "]");
        //ui->listWidgetUser->addItem(count);
        QList<QListWidgetItem *> item;
        for(int i = 0; i < m_userFriends.m_countArry.size(); ++i)
        {
          if(item = ui->listWidgetUser->findItems(m_userFriends.m_countArry[i], Qt::MatchFixedString),item.count() == 0)
          {
               QListWidgetItem *iter = new  QListWidgetItem(m_userFriends.m_countArry[i], ui->listWidgetUser);
               ui->listWidgetUser->addItem(iter);
          }
        }
    }
}

void ChatList::on_userListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString tocount = ui->listWidgetUser->currentItem()->text();
    //QString tocount = item->text();
    MainWindow *chat; //= m_chatfrom.value(tocount);
    if(!m_chatfrom.contains(tocount))
    {
        //QDebug()<<
        chat = new MainWindow(m_userInfo.m_count, m_serverIP, m_serverPort, this->m_udpSocket);
        chat->setWindowTitle(tocount);
        m_chatfrom.insert(tocount, chat);
    }
    else
        chat = m_chatfrom.value(tocount);
    //chat->setWindowFlags(Qt::FramelessWindowHint);
    //chat->setAttribute(Qt::WA_TranslucentBackground);
    chat->show();
}
