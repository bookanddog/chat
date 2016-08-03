#ifndef USERFRIEND_H
#define USERFRIEND_H

/*//从套接字发出去的时候没有重载<<操作符，不能转化为流数据，不能使用，考虑以后实现重载
#include "user.h"

class UserFriend : public User
{
public:
    bool          m_nowfriend;
    QString       m_group;
};
*/

#include <QObject>

class UserFriend
{
public:
    QVector<QString>     m_countArry;
    QVector<QString>     m_nicknameArry;
    QVector<int>         m_stateArry;
    QVector<QString>     m_mottoArry;
    QVector<bool>        m_nowfriendArry;
    QVector<QString>     m_groupArry;
};

#endif // USERFRIEND

