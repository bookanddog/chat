#ifndef SQLDB_H
#define SQLDB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
//#include <QVector>

//#include "user.h"
#include "userinfo.h"
#include "userfriend.h"
//#include <QtSql/q>

class SqlDB : public QObject
{
public:
    SqlDB();

    //function
    void connectDB();
    void closeDB();
    void getUserInfo(QString count);
    void getUserFriends(QString count);
    void getUserNet(const QString count, QString &ip, QString &port);
    void updateUsernet(QString count, QString ip, QString port);

    //public menber
    //QString ucount;
    //QString upwd;
    //QString uname;
    //QStringList ufriemdsList;
    //QString ufriend;
    //int     state;

    //私有还是公有有待考虑
    //QVector<UserFriend>      m_userFriends;
    UserInfo                 m_userInfo;
    UserFriend               m_userFriends;


private:
    QSqlDatabase             m_db;
    
    //目前只是登录验证，以后再添加
    //QStringList strListUser;
   // QStringList strListId;
    //QStringList strListName;

};
#endif // SQLDB
