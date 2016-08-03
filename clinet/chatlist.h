#ifndef CHATLIST_H
#define CHATLIST_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QMessageBox>
#include <QListWidget>//这个不是从ui中继承了么,怎么还需要声明
#include "mainwindow.h"
#include "userinfo.h"
#include "userfriend.h"

namespace Ui {
class ChatList;
}

class ChatList : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatList(QString count, QString servip, QString servport, quint16 clientport, QWidget *parent = 0);
    //ChatList(QString count);
    ~ChatList();

    void init();

private slots:
    void on_userListWidget_itemDoubleClicked(QListWidgetItem* item);
    void recvMsg();
    //void on_quit();

private:
    Ui::ChatList *ui;

    UserInfo               m_userInfo;
    //QVector<UserFriend>    m_userFriends;
    UserFriend             m_userFriends;
    //用户信息，有些考虑用指针，因为可能没有填写信息，占用内存
    /*
    QString       m_count;
    QString       *m_nickname;
    int           *m_qq;
    QString       *m_emali;
    int           *m_phone;
    QString       *m_sex;
    QString       *m_birthday;//有没有日期类型可以直接使用
    QString       *m_motto;//  座右铭
    */

    QUdpSocket    *m_udpSocket;
    //服务器信息
    QString       m_serverIP;
    QString       m_serverPort;
    quint16       m_clientPort;//客户端tcp端口号

    //MainWindow    *m_chatform;
    QHash<QString, MainWindow *> m_chatfrom;
};

#endif // CHATLIST_H
