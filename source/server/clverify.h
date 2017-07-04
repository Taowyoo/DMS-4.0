#ifndef CLVERIFY_H
#define CLVERIFY_H
#include <string>
#include "data.h"
#include "sexcept.h"
#include "Deciphering.h"
using namespace std;
class Clverify
{
public:
    Clverify(const string& ip,short port);//建立连接
    void registerClient();
    //int usersign() throw(DBException);
    ~Clverify();
private:
    int clrecv();//接收数据
    int clsend(int result);//发送结果
    int cl_sockfd;
    int client_sockfd;//已废弃变量
};

#endif
