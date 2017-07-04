#ifndef _DATA_H
#define _DATA_H
#include <unistd.h>//pid_t等uc数据类型和函数
#include <string>
//登入登出日志记录
struct LogRec
{
    char logname[32];//用户登陆名
    char logpip[32];//登陆IP地址
    pid_t logpid;//登陆进程号
    long logtime;//登入或登出时间

};
//匹配日志记录
struct MLogRec
{
    char logname[32];//用户登陆名
    char logpip[32];//登陆IP地址
    pid_t logpid;//登陆进程号
    long logtimein;//登入时刻
    long logtimeout;//登出时刻
    long timelong;//在线时长
};

struct User
{
char name[32];
char password[32];
char email[32];
char phone[32];
};


struct table{
    std::string name;
    std::string timelong;
    float cost;
    long second;
    unsigned int times;
};
/*
struct table{
    char name[20];
    char timelong[20];
    float cost;
    int second;
};
*/




#endif //_DATA_H
