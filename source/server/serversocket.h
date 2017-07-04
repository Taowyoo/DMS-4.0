//声明服务器端socket接收类
#include "sexcept.h"
#include "logqueue.h"
#include <string>
#include <QTcpServer>
using namespace std;
class ServerSocket
{
public:
       int m_sockfd;//套接字描述符
       QTcpServer *tcpServer;
public:
       ServerSocket(short port,const string ip);
       void acceptClient_old()throw (SocketException);
       void acceptClient();
};
