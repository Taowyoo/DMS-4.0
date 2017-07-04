#include "workthread.h"
#include "socketsender.h"
#include <iostream>

void WorkThread::run()
{
    try{
        LogReader reader("./wtmpx","./logins.dat");
        SocketSender sender("127.0.0.1",2006,"./fail.dat",this);
        Client client(reader,sender);
        client.dataMine();
    }
    catch(ClientException ex)
    {
        std::cout<<ex.what()<<std::endl;
    }
}

void WorkThread::update(MLogRec log)
{
    emit (updates(log));//send signal
    //emit (update (QString (text.c_str ())))
}
