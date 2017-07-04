
#ifndef _EXCEPT_H
#define _EXCEPT_H
#include <string>
using namespace std;

class ClientException : public exception
{
private:
    string m_msg;
public:
    ClientException():m_msg("客户机异常"){}
    ClientException(const string& msg):m_msg("客户机异常")
    {
        m_msg=msg;
        m_msg+="!";
    }
    ~ClientException()throw(){}
    const char* what()
    {
        return m_msg.c_str();
    }

};

class BackupException : public ClientException
{
public:
    BackupException() : ClientException("备份异常"){}
    BackupException(const string& msg) : ClientException(msg){}
};

class ClientSocketException : public ClientException
{
public:
    ClientSocketException():ClientException("客户机套接字异常"){}
    ClientSocketException(const string& msg):ClientException(msg){}
};

class ReadException : public ClientException
{
public:
    ReadException():ClientException("读取异常"){}
    ReadException(const string& msg):ClientException(msg){}
};

class SaveException : public ClientException
{
public:
    SaveException():ClientException("保存异常"){}
    SaveException(const string& msg):ClientException(msg){}
};

class SendException : public ClientException
{
public:
    SendException():ClientException("发送异常"){}
    SendException(const string& msg):ClientException(msg){}
};
class SocketException : public ClientException
{
public:
    SocketException():ClientException("Socket异常"){}
    SocketException(const string& msg):ClientException(msg){}
};
#endif // _EXCEPT_H
