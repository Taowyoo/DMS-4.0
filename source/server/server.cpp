// 实现服务器类
#include "server.h"
#include "tothread.h"
#include "data.h"
#include "logqueue.h"
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
//#include "Server.moc"
using namespace std;


Server::Server(LogDao& dao, const string& ip,
               short logPort,short registerPort)
throw(ServerException)
    : m_store (dao),      m_socket(logPort,ip),      m_clverify(ip, registerPort) {}

void Server::run()
{
    try {
        this->dataMine ();
    }
    catch (ServerException& ex) {
        cout << ex.what () << endl;
        exit(-1);
    }
}

void Server::dataMine ()
throw (ServerException){
    try {
        // 启动存储线程...
        m_clverify.registerClient();
        m_store.start();
        //cout<<"启动存储线程wanbi kaishiyunxing xiayi "<<endl;
        m_socket.acceptClient();
        //pause();

    }
    catch (ServerException& ex){
        throw;
    }
}
