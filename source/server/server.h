#include "serversocket.h"
#include "tothread.h"
#include "clverify.h"
#include <QThread>
class Server : public QThread
{
    //Q_OBJECT
private:
    StoreThread m_store;
    ServerSocket m_socket;
    Clverify m_clverify;
    void run();
public:
    Server(LogDao& dao, const string& ip,
           short logPort,short registerPort)throw(ServerException);//初始化服务器端LogDao& dao
    void dataMine()throw(ServerException);//数据接收及存储
};
