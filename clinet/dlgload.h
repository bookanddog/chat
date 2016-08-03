//****************************************
// 处理与登录相关动作
// 所有的tcp消息也在这里处理
//
//*************************************
#ifndef DLGLOAD_H
#define DLGLOAD_H
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
#include <QDialog>
#include <QHostAddress>

#include "chatlist.h"
//#include "userinfo.h"

namespace Ui {
class DlgLoad;
}

class DlgLoad : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLoad(QWidget *parent = 0);
    ~DlgLoad();

private slots:
    void on_pushButtonLoad_clicked();
    void on_ready_Read();

private:
    Ui::DlgLoad *ui;
    QString      m_count; //账户
    QString      m_pwd;   //密码
    //UserInfo    *m_userInfo;//用户信息

    ChatList     *m_chatList;//转到登录成功后的界面
    QTcpSocket  *m_tcpSocket;//tcp连接
    QString      m_serverIP;   //服务器ip
    QString      m_serverPort;
    quint16      m_clientPort;//客户端端口，当多个实例运行时用来标记不同实例对应绑定的端口号（tcp端口号,系统内核随机分配的）；
};

#endif // DLGLOAD_H
