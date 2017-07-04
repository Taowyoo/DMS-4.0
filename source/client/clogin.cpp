#include "clogin.h"
#include "except.h"
#include "data.h"
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "encrypt.h"
using namespace std;



CLogin::CLogin(const string& ip,short port)
{
    cout << "连接服务器开始..." << endl;
    if ((clogin_sockfd = socket (AF_INET,SOCK_STREAM, 0)) == -1)
    {
        cout<<"CLogin::CLogin get socket error!"<<endl;
    }
    //throw SocketException ();
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons (port);
    addr.sin_addr.s_addr = inet_addr (ip.c_str ());
    if (connect (clogin_sockfd, (sockaddr*)&addr,sizeof (addr)) == -1)
    {
        cout<<"CLogin::CLogin connect error!"<<endl;
    }

    //throw SocketException ();
    cout << "连接服务器完成。" << endl;
}

void CLogin::cloginsend(const char name[32],const char password[32])
throw (SendException){
    using encryption::encrypt;
    User user;
    encrypt encrypt1(name);
    encrypt encrypt2(password);
    strcpy(user.name,encrypt1.cipherText());
    strcpy(user.password,encrypt2.cipherText());
    char test[32];
    test[0]='#';
    strcpy(user.email,test);
    strcpy(user.phone,test);
    cout<<"CLogin::cloginsend :"<<endl;
    //user.email={'\0'};
    //user.phone={'\0'};
    cout<<"kehuduan :"<<user.name<<"     "<<user.password<<endl;
    //strcpy(user.name,name);
    //strcpy(user.password,password);
    if (send (clogin_sockfd, &user,sizeof (user), 0) == -1)
        throw SendException ();

}

void CLogin::usersign(User user)
throw (SendException){
    if (send (clogin_sockfd, &user,sizeof (user), 0) == -1)
        throw SendException ();
}

int CLogin::csignrecv() throw (SendException)
{
    //sendtext stext;
    int result;
    int i = 0;
    while(1){
        i=recv(clogin_sockfd,(char*)&result,sizeof(result),0);
        if(i>0)
        {
            /*
    switch(stext.result){
    case 0://0用户注册成功
    cout<<"用户注册成功"<<endl;
    break;
    case 1://1该用户名已被使用，请更换用户名
    cout<<"该用户名已被使用，请更换用户名"<<endl;
    break;
    case 2://1该用户名已被使用，请更换用户名
    cout<<"success!"<<endl;
    default:
    cout<<"请重新输入用户名和密码"<<endl;
    }*/

            break;
        }else {
            throw SendException("CLogin::csignrecv(): recv failed!");
        }
    }
    return result;
}
/*
int CLogin::cloginrecv()
{
    int result=3;
    //while(1){
    if(recv(clogin_sockfd,(char*)&result,sizeof(result),0)>0)
        ;
    cout<<result<<endl;
    {
    switch(result){
    case 0://0为ID不存在
    cout<<"用户名不存在"<<endl;
    break;
    case 1://1为密码错误
    cout<<"密码错误"<<endl;
    break;
    case 2://2为验证成功
    cout<<"验证成功"<<endl;
    break;
    default:
    cout<<"请重新输入用户名和密码"<<endl;
    }break;
    //}
//}
    return result;
}*/
//CLogin::close()
//{
//    CLogin::
//}

CLogin::~CLogin()
{
    close(clogin_sockfd);
}
