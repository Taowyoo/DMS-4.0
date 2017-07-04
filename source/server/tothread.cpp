
#include <iostream>
#include <unistd.h>    //提供通用的文件、目录、程序及进程操作的函数
#include <sys/socket.h>// socket数据类型定义头文件
#include <arpa/inet.h> //提供IP地址转换函数
#include <pthread.h>
#include "tothread.h"
#include "Deciphering.h"
#include "mysqldao.h"
using namespace std;

LogThread::LogThread(){}
LogThread::~LogThread(){}
// 启动线程
void LogThread::start (void)
throw (ThreadException) {
    cout << "启动线程开始..." << endl;
    pthread_t id;
    int ret;
    if((ret=pthread_create(&id,NULL,task,this)))
        throw ThreadException("线程启动异常");
    cout << "启动线程完成。" << endl;
}
// 线程过程
void* LogThread::task (void * object) {
    return ((LogThread *) object)->anything(object);
}

void* LogThread::anything(void* arg)
{
    pthread_detach (pthread_self ());
    static_cast<LogThread*> (arg)->run ();
    return NULL;
}

ClientThread::ClientThread (int connfd) :
    m_connfd (connfd){}
ClientThread::~ClientThread(){}
void ClientThread::run() throw (ThreadException)
{
    MLogRec mlogrec;
    int log_num=0;
    //实现一条条接收匹配日志记录
    ssize_t rlen;
    while(1)
    {
        if((rlen=recv(m_connfd,(char*)&mlogrec,sizeof(mlogrec),0))>0)
        {
            ++log_num;
            mlogrec.logpid=ntohl(mlogrec.logpid);
            mlogrec.logtimein=ntohl(mlogrec.logtimein);
            mlogrec.logtimeout=ntohl(mlogrec.logtimeout);
            mlogrec.timelong=ntohl(mlogrec.timelong);

            logqueue<<mlogrec;
        }else
            break;
    }
    //统计共接收有多少匹配记录
    //cout<<logqueue.m_logs.front().logname<<endl;
    cout<<"本次共接收了"<<log_num<<"条记录"<<endl;
}


StoreThread::StoreThread (LogDao& dao) :
    m_dao (dao) {}
StoreThread::~StoreThread(){}
// 线程处理
void StoreThread::run() throw (ThreadException)
{
    MLogRec log;
    int i=0;
    cout<<"start insert into database!"<<endl;
    m_dao.remove();
    while(1){
        ++i;
        //弹出一条匹配日志记录
        logqueue>>log;
        //cout << "storethread" << log.logname << endl;
        try{
            //插入到文件或数据库
            m_dao.insert(log);

        }catch(DBException& dex){
            cout<<dex.what()<<endl;
        }
    }

    cout<<"弹出"<<i<<"一条匹配日志记录"<<endl;
}

RegisterThread::RegisterThread (int connfd) :
    m_connfd (connfd) {}

RegisterThread::~RegisterThread(){}

void RegisterThread::run() throw (ThreadException)
{
    MysqlDao m_dao;
    User user;
    int result;
    int status = 0;
    while(1){
        status = recv(m_connfd,(char*)&user,sizeof(user),0);
        if(status>0)
        {
            cout<<"Clverify::clrecv():recv success! begin to confirm user info!"<<endl;
            cout << "user.name: "<<user.name
                 << " user.password: "<< user.password << endl;
            if(user.email[0]=='#'&&user.phone[0]=='#')
            {
                cout<<"Login request!"<<endl;
                Deciphering decipher1(user.name);
                Deciphering decipher2(user.password);
                //MysqlDao sqldao;
                strcpy(user.name,decipher1.decipher());
                strcpy(user.password,decipher2.decipher());
                cout<<"user.name: "<<user.name<<" user.password: "<<user.password<<endl;
                result=m_dao.select(user);
                cout<<"confirm result: "<<result<<endl;
                //return result;
                if (send (m_connfd, &result,sizeof (result), 0) == -1)
                    throw SendException ();
                else
                    cout<<"验证结果发送成功"<<endl;
                if(result == 2)
                    break;
            }
            else
            {
                cout<<"registration request!"<<endl;
                result=m_dao.select(user);
                if(result==0)
                {
                    m_dao.userinsert(user);
                    //stext.result=result;
                    //result=3;
                    //return result;//用户注册成功
                    cout<<"用户注册成功"<<endl;
                }
                else if(result==1||result==2)
                {
                    //result=4;
                    //return result;//该用户名已被使用，请更换用户名
                    cout<<"该用户名已被使用，请更换用户名"<<endl;
                }
                else
                    throw ThreadException("注册失败");
                if (send (m_connfd, &result,sizeof (result), 0) == -1)
                    throw SendException ();
                else
                    cout<<"验证结果发送成功"<<endl;
            }
        }
        else if(status == -1)
            throw ThreadException("RegisterThread::run(): recv failed!");
        else
            usleep(1000);
    }
}

LoginThread::LoginThread (int sockfd) :
    m_sockfd (sockfd) {}

LoginThread::~LoginThread(){}
//Login 线程处理

void LoginThread::run() throw (ThreadException)
{
    while(1){
        struct sockaddr_in client_addr;
        socklen_t c_size=sizeof(struct sockaddr_in);
        int client_sockfd=accept(m_sockfd,(struct sockaddr*)&client_addr,&c_size);
        if(client_sockfd!=-1)
        {
            cout<<"Clverify: 客户机连接成功! client_sockfd = "<< client_sockfd <<endl;
            //建立新线程 用来处理登录和注册
            RegisterThread* rtd= new RegisterThread(client_sockfd);
            rtd->start();

        }
        else
        {
            close(m_sockfd);
            throw SocketException("Clverify: 客户机连接失败，无法接收数据");
        }
    }
}

AcceptThread::AcceptThread (int sockfd) :
    m_sockfd (sockfd) {}

AcceptThread::~AcceptThread(){}

void AcceptThread::run() throw (ThreadException)
{
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
        }
        else
        {
            close(m_sockfd);
            throw SocketException("ServerSocket:客户机连接失败，无法接收数据");
        }
    }
}
