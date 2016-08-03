//*****************************
// 保存用户信息，考虑是不是不需要保存，
//    有基本的count与nickname就好了
// 然后待需要的时候再从服务器获取
// 这样就有哪一个花销比较大的问题了
// 回去后断网测试qq怎么搞的
//******************************
#ifndef USERINFO_H
#define USERINFO_H

//#include <QObject>
#include "user.h"

class UserInfo : public User
{
public:
    //QString        m_count;
    //QString        m_nickname;
    QString        m_pwd;
    int            m_qq;
    QString        m_email;
    int            m_phone;
    QString        m_sex;
    QString        m_birthday;
    //int            m_state;
    //QString        m_motto;
    //QStringList    m_group;
};
#endif // USERINFO


