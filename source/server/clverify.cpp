#include "mysqldao.h"
#include "data.h"
#include "clverify.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sexcept.h"
#include "tothread.h"

Clverify::Clverify(const string& ip,short port)//建立连接
{
    cout<<"Clverify: start initializing ServerSocket!!"<<endl;
    int i;
    cl_sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(cl_sockfd==-1)
        throw SocketException("客户端连接失败");
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr(ip.c_str());
    i=bind(cl_sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(i==-1)
        throw SocketException("绑定套接字失败");
    i=listen(cl_sockfd,1024);
    if(i==-1)
        throw SocketException("侦听套接字失败");
    cout<<"Clverify: initialize ServerSocket success!!"<<endl;
}
void Clverify::registerClient()
{
    cout<<"Clverify: 等待客户机连接..."<<endl;
    LoginThread* rtd= new LoginThread(cl_sockfd);
    rtd->start();

}

int Clverify::clrecv()//接收数据并判断是否相同
{
    //sendtext stext;
    User user;
    int result;
    MysqlDao sqldao;
    while(1){
        struct sockaddr_in client_addr;
        socklen_t c_size=sizeof(struct sockaddr_in);
        int client_sockfd=accept(cl_sockfd,(struct sockaddr*)&client_addr,&c_size);
        if(recv(client_sockfd,(char*)&user,sizeof(user),0)>0)
        {cout<<"Clverify::clrecv():recv success! begin to confirm user info!"<<endl;
            cout << "user.name: "<<user.name
                 << "user.password: "<< user.password << endl;
            if(user.email[0]=='#'&&user.phone[0]=='#')
            {
                cout<<"Login request!"<<endl;

                Deciphering decipher1(user.name);
                Deciphering decipher2(user.password);
                //MysqlDao sqldao;
                strcpy(user.name,decipher1.decipher());
                strcpy(user.password,decipher2.decipher());
                cout<<"user.name: "<<user.name<<" user.password: "<<user.password<<endl;
                result=sqldao.select(user);
                cout<<"confirm result: "<<result<<endl;
                return result;
            }else
            {
                cout<<"registration request!"<<endl;
                result=sqldao.select(user);
                if(result==0)
                {
                    sqldao.userinsert(user);
                    //stext.result=result;
                    //result=3;
                    return result;//用户注册成功
                }else if(result==1||result==2)
                {
                    //result=4;
                    return result;//该用户名已被使用，请更换用户名
                }else
                    throw SocketException("注册失败");
            }
        }else
            throw SocketException("用户名及密码接收失败");
    }
}
/*
int Clverify::usersign() throw(DBException)
{
    User user;
    int result;
    MysqlDao sqldao;
    int size;
    while(1){
        struct sockaddr_in client_addr;
        socklen_t c_size=sizeof(struct sockaddr_in);
        client_sockfd=accept(cl_sockfd,(struct sockaddr*)&client_addr,&c_size);
        if(size=recv(client_sockfd,(char*)&user,sizeof(user),0)>0)
        {
                result=sqldao.select(user);
                if(result==0)
                {
                    sqldao.userinsert(user);
                    return 0;//用户注册成功
                }else if(result==1||result==2)
                {
                    return 1;//该用户名已被使用，请更换用户名
                }else
                    throw SocketException("注册失败");
        }else
    throw SocketException("用户名及密码接收失败");
    }
    return result;

}*/
int Clverify::clsend(int result)//发送结果
{
    int rs=result;
    if (send (client_sockfd, &result,sizeof (result), 0) == -1)
        throw SendException ();
    else
        cout<<"验证结果发送成功"<<endl;

    return rs;
}

Clverify::~Clverify()
{
    close(cl_sockfd);
}
