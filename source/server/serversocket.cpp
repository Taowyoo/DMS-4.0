//实现服务器端socket接收类
#include "serversocket.h"
#include "tothread.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
// 构造器 和客户端进行连接
ServerSocket::ServerSocket(short port,const string ip)
{
    cout<<"ServerSocket: start initializing ServerSocket!!"<<endl;
    int i;
    m_sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(m_sockfd==-1)
        throw SocketException("客户端连接失败");
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr(ip.c_str());
    i=bind(m_sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(i==-1)
        throw SocketException("绑定套接字失败");
    i=listen(m_sockfd,1024);
    if(i==-1)
        throw SocketException("侦听套接字失败");
    cout<<"ServerSocket: initialize ServerSocket success!!"<<endl;
}
// 等待客户机连接
void ServerSocket::acceptClient_old() throw (SocketException)
{
    cout<<"ServerSocket: 等待客户机连接..."<<endl;

    while(1){
        struct sockaddr_in client_addr;
        socklen_t c_size=sizeof(struct sockaddr_in);
        int client_sockfd=accept(m_sockfd,(struct sockaddr*)&client_addr,&c_size);
        if(client_sockfd!=-1)
        {
            //建立新线程 用来读取数据
            ClientThread* ctd= new ClientThread(client_sockfd);
            ctd->start();
            cout<<"ServerSocket: 客户机连接成功"<<endl;
        }else
        {
            close(m_sockfd);
            throw SocketException("客户机连接失败，无法接收数据");
        }
    }

}

void ServerSocket::acceptClient()
{
    cout<<"ServerSocket: 等待客户机连接..."<<endl;
    AcceptThread* atd= new AcceptThread(m_sockfd);
    atd->start();

}
