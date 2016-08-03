#include <QMessageBox>
#include <QVariant>
#include "sqldb.h"

SqlDB::SqlDB()
{

}

void SqlDB::connectDB()
{   //**********************************************************************************************
    //**使用的数据库驱动程序,连接数据库注意集中情况：
    //** 1，主要是版本问题，32位qt对于32位postgresql；
    //** 2，.pro中加入包含和依赖目录;
    //** 3,libeay32.dll,libpq.dll,ssleay32.dll,libintl.dll这几个文件放在编译好的exe或者可执行文件相同目录下
    //******************************************************************************************
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("chat");
    m_db.setUserName("postgres");
    m_db.setPassword("123");
    if(!m_db.open())
    {
         QMessageBox::critical(NULL, "Connect to db...", "Connect failed.");
    }
}

void SqlDB::closeDB()
{
    m_db.close();
}

void SqlDB::getUserNet(const QString count, QString &ip, QString &port)
{
    this->connectDB();
    QSqlQuery query;
    query.exec("select ip, port from \"user\" where count = '" + count + "';");
    if(query.next())
    {
        ip = query.value(0).toString();
        port = query.value(1).toString();
    }
    else
    {//错误处理
    }
    this->closeDB();
}

void SqlDB::updateUsernet(QString count, QString ip, QString port)
{
    this->connectDB();

    QSqlQuery query;
    if(!query.exec("update \"user\" set ip = '" + ip + "', port = '" + port + "' where count = '" + count + "';"))
         QMessageBox::critical(NULL, "exec", "Exec failed.");
    this->closeDB();

}

void SqlDB::getUserInfo(QString count)
{
    this->connectDB();

    //注意后面的清空操作，这里要覆盖所以可以暂时忽略
    //**********************+++++++++++++++++++++++++++
    QSqlQuery query;
    //uname.clear();
    m_userInfo.m_state = -1;

    query.exec("select pwd, nickname, qq, email, phone, sex, birthday, state, motto from \"user\" where count = '" + count + "';");
    if(query.next())
    {
        /*
        ucount = query.value(0).toString();
        upwd = query.value(1).toString();
        uname = query.value(2).toString();
        state = query.value(8).toInt();
        */
        m_userInfo.m_count = count;
        m_userInfo.m_pwd = query.value(0).toString();
        m_userInfo.m_nickname = query.value(1).toString();
        m_userInfo.m_qq = query.value(2).toInt();
        m_userInfo.m_email = query.value(3).toString();
        m_userInfo.m_phone = query.value(4).toInt();
        m_userInfo.m_sex = query.value(5).toInt();
        m_userInfo.m_birthday = query.value(6).toString();
        m_userInfo.m_state = query.value(7).toInt();
        m_userInfo.m_motto = query.value(8).toString();
    }
    else
    {
        //失败或者为空的情况，待添加;
    }
    this->closeDB();

}

void SqlDB::getUserFriends(QString count)
{
    this ->connectDB();
    QSqlQuery query;
    m_userFriends.m_countArry.clear();
    m_userFriends.m_groupArry.clear();
    m_userFriends.m_nowfriendArry.clear();
    m_userFriends.m_nicknameArry.clear();
    m_userFriends.m_stateArry.clear();
    m_userFriends.m_mottoArry.clear();
    //UserFriend userfriend;
      //联合查询，应该没有写错
    query.exec("select \"friendShip\".fcount, \"friendShip\".fgroup, \"friendShip\".nowfriend, \"user\".nickname, \"user\".state, \"user\".motto from  \"friendShip\" inner join  \"user\" on \"friendShip\".fcount = \"user\".count where \"friendShip\".ucount = '" + count + "';");
    while(query.next())
    {
        m_userFriends.m_countArry.append(query.value(0).toString());
        m_userFriends.m_groupArry.append(query.value(1).toString());
        m_userFriends.m_nowfriendArry.append(query.value(2).toBool());
        m_userFriends.m_nicknameArry.append(query.value(3).toString());
        m_userFriends.m_stateArry.append(query.value(4).toInt());
        m_userFriends.m_mottoArry.append(query.value(5).toString());
        /*
        userfriend.m_count = query.value(0).toString();
        userfriend.m_group= query.value(1).toString();
        userfriend.m_nowfriend= query.value(2).toBool();
        userfriend.m_nickname= query.value(3).toString();
        userfriend.m_state= query.value(4).toInt();
        userfriend.m_motto= query.value(5).toString();

        m_userFriends.append(userfriend);
        */
    }
    /*//前面加一个判断
    else {
        //查询失败的处理，待添加；
    }
    */
    this->closeDB();

}
