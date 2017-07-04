#ifndef DATA_H
#define DATA_H

#endif // DATA_H
#ifndef _DATA_H
#define _DATA_H
#include <unistd.h>//
//
struct LogRec
{
    char logname[32];//
    char logpip[32];//
    pid_t logpid;//
    long logtime;//

};
//
struct MLogRec
{
    char logname[32];//
    char logpip[32];//
    pid_t logpid;//
    long logtimein;//
    long logtimeout;//
    long timelong;//

};
struct User
{
char name[32];
char password[32];
char email[32];
char phone[32];
};

#endif //_DATA_H
