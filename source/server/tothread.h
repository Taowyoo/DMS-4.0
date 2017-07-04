#ifndef TOTHREAD_H
#define TOTHREAD_H

#include "logqueue.h"
//#include "storethread.h"
#include "logdao.h"
#include "sexcept.h"
#include <iostream>

static LogQueue logqueue;

class LogThread
{
public:
    LogThread();
    virtual ~LogThread();
    void start (void)
        throw (ThreadException);
    virtual void run() throw (ThreadException)=0;
 private:
    static void* task (void * object);
    void* anything(void* arg);
};

class ClientThread:public LogThread
{
public:
    ClientThread (int connfd) ;
    ~ClientThread();
    void run() throw (ThreadException);
private:
     int m_connfd; // 通信套接字
};
class StoreThread:public LogThread
{
public:
    StoreThread (LogDao& dao);
    ~StoreThread();
    void run() throw (ThreadException);
private:
    LogDao& m_dao; // 数据访问对象
};
class RegisterThread:public LogThread
{
public:
    RegisterThread (int connfd) ;
    ~RegisterThread();
    void run() throw (ThreadException);
private:
     int m_connfd; // 通信套接字
     //LogDao& m_dao; // 数据访问对象
};

class LoginThread:public LogThread
{
public:
    LoginThread (int sockfd) ;
    ~LoginThread();
    void run() throw (ThreadException);
private:
     int m_sockfd; // 通信套接字

};

class AcceptThread:public LogThread
{
public:
    AcceptThread (int sockfd) ;
    ~AcceptThread();
    void run() throw (ThreadException);
private:
     int m_sockfd; // 通信套接字

};
#endif
