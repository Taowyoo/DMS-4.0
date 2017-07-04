#ifndef _SEXCEPT_H
#define _SEXCEPT_H
#include <string>
using namespace std;

//服务端异常
class ServerException : public exception
{
private:
    string m_msg;
public:
    ServerException () :
        m_msg ("服务器异常！") {}
    ServerException (const string& msg) :
        m_msg ("服务器异常：")
    {
        m_msg += msg;
        m_msg += "！";
    }
    ~ServerException ()  throw() {}
    const char* what () throw()
    {
        return m_msg.c_str();
    }

};

//网络通信异常
class SocketException : public ServerException
{
public:
    SocketException(): ServerException("网络通信异常！") {}
    SocketException(const string& msg) : ServerException(msg) {}
};

//数据库异常
class DBException : public ServerException
{
public:
    DBException() : ServerException("数据库异常！") {}
    DBException(const string& msg) : ServerException(msg) {}
};

//线程异常
class ThreadException : public ServerException
{
public:
    ThreadException() : ServerException("线程异常！"){}
    ThreadException(const string& msg) : ServerException(msg){}
};

class SendException :public ServerException {
public:
    SendException () :ServerException ("发送异常") {}
    SendException (const string& msg) :ServerException (msg) {}
};

#endif // _SEXCEPT_H
