﻿#include <QMessageBox>
#include "tcpconthread.h"


//这里先直接实现通信这个线程不必使用目前
//这里的socketdescriptor（）什么意思
TcpConThread::TcpConThread(int socketDescriptor, QObject *parent) : QThread(parent), m_socketDescriptor(socketDescriptor)
{}

/****************************************************************************
**
** Creates a QTcpSocket, use Constructer passed in socketDescriptor to
** set the socket descriptor, and then stores the QTcpSocket in an internal
** list of pending connections.
** Finally newConnection() is emitted.
**
****************************************************************************/
void TcpConThread::run()
{
    m_tcpSocket = new QTcpSocket;

    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(on_Ready_Read()));

    if(!m_tcpSocket->setSocketDescriptor(m_socketDescriptor))
    {
        emit error(m_tcpSocket ->error());
        return;
    }
    exec();
}

void TcpConThread::on_Ready_Read()
{
    m_db = new SqlDB;

    QByteArray inblock = m_tcpSocket->readAll();
    QDataStream in(&inblock, QIODevice::ReadOnly);
    quint16 dataGramSize;
    QString inmsg;
    in >> dataGramSize >> inmsg;

    //注册，以后扩充或者用网页注册
    if("REGISTRT" == inmsg)
    {}
    else if("LOGIN" == inmsg)//登录，以后扩充
    {
        QByteArray outblock;
        QDataStream out(&outblock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        QString answerMsg;

        QString count;
        QString pwd;
        in >> count >> pwd;

        m_db->getUserInfo(count);

        if(count == m_db->m_userInfo.m_count && pwd == m_db->m_userInfo.m_pwd)
        {

            answerMsg = "LOGIN_SUCCESS";
        }
        else if(m_db->m_userInfo.m_state == -1)
        {

            answerMsg = "NO_COUNT";
        }
        else
        {
            answerMsg = "NO_COUNT";
        }
        out << (quint16)0 << answerMsg ;
        out.device()->seek(0);
        out << (quint16)(outblock.size() - sizeof(quint16));

        m_tcpSocket->write(outblock);
    }//待修改
    /*
    else if( msg == "NEW_CONN")
    {
        QString count;

        in >> count;
        m_db->getUserFriends(count);

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        QString msg = "FRIENDS";
        out << (quint16)0 << msg << m_db->ufriend;
        out.device()->seek(0);
       //m_udpSocket->writeDatagram(block.data(), block.size(), QHostAddress::LocalHost, 6869);
        out << (quint16)(block.size() - sizeof(quint16) + );

        m_tcpSocket->write(block);
    }
    */
}
