// 实现网络日志发送器类
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
#include "socketsender.h"
// 构造器
SocketSender::SocketSender (const string& ip,
short port, const string& failFile,WorkThread* work) :
    m_ip (ip), m_port (port),

    m_failFile (failFile),m_work(work) {}
// 发送日志
void SocketSender::sendLog (
    list<MLogRec>& logs)
    throw (SendException) {
    cout << "发送日志开始..." << endl;
    try {
        try {
            // 读取发送失败文件
            readFailFile (logs);
        }
        catch (ReadException& ex) {
            cout << "无发送失败文件！"
                << endl;
        }
        // 连接服务器
        connectServer ();
        // 发送数据
        sendData (logs);
    }
    catch (SocketException& ex) {
        // 保存发送失败文件
        saveFailFile (logs);
        throw SendException ("连接错误");
    }
    catch (SendException& ex) {
        // 保存发送失败文件
        saveFailFile (logs);
        throw SendException ("发送失败");
    }
    cout << "发送日志完成。" << endl;
}
// 连接服务器
void SocketSender::connectServer (void)
    throw (SocketException) {
    cout << "连接服务器开始..." << endl;
    if ((m_sockfd = socket (AF_INET,
        SOCK_STREAM, 0)) == -1)
        throw SocketException ();
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons (m_port);
    addr.sin_addr.s_addr = inet_addr (
        m_ip.c_str ());
    if (connect (m_sockfd, (sockaddr*)&addr,
        sizeof (addr)) == -1)
        throw SocketException ();
    cout << "连接服务器完成。" << endl;
}
// 读取发送失败文件
void SocketSender::readFailFile (
    list<MLogRec>& logs)
    throw (ReadException) {
    cout << "读取发送失败文件开始..." << endl;
    ifstream ifs (m_failFile.c_str (),
        ios::binary);
    if (! ifs)
        throw ReadException ();
    MLogRec log;
    while (ifs.read ((char*)&log,
        sizeof (log)))
        logs.push_front (log);
    if (! ifs.eof ())
        throw ReadException ();
    ifs.close ();
    unlink (m_failFile.c_str ());
    cout << "读取发送失败文件完成。" << endl;
}
// 发送数据
void SocketSender::sendData (
    list<MLogRec>& logs)
    throw (SendException) {
    cout << "发送数据开始..." << endl;
    int i=0;
    for (list<MLogRec>::iterator it=logs.begin();it!=logs.end();++it)
    {
	
        MLogRec log = *it;
        //print test
        /*
        cout<<log.logname<<" "<<log.logpip<<" "<<log.logpid
              <<" "<<log.logtimein<<" "<<log.logtimeout<<" "<<
                log.timelong<<endl;
                */
        ;
        log.logpid = htonl (log.logpid);
        log.logtimein = htonl (log.logtimein);
        log.logtimeout=htonl (log.logtimeout);
        log.timelong = htonl (log.timelong);
        if (send (m_sockfd, &log,
            sizeof (log), 0) == -1) {
            close (m_sockfd);
            throw SendException ();
        }

        if (m_work) {//signal MRecLog
            //ostringstream oss;
            //oss << logs.front ();
	    //LogRec log1=logs.front();
            m_work->update (logs.front());
        }
        // 删除发送成功的匹配日志记录，
        // 剩余的记录存入发送失败文件
        //logs.pop_front ();
	++i;
    }
    close (m_sockfd);
    cout << "发送数据完成。" <<i<< endl;
}
// 保存发送失败文件
void SocketSender::saveFailFile (
    list<MLogRec>& logs)
    throw (SaveException) {
    cout << "保存发送失败文件开始..." << endl;
    if (! logs.empty ()) {
        ofstream ofs (m_failFile.c_str (),
            ios::binary);
        if (! ofs)
            throw SaveException ();
        while (! logs.empty ()) {
            ofs.write ((const char*)&logs.front (),
                       sizeof (MLogRec));
            logs.pop_front ();
        }
        ofs.close ();
    }
    cout << "保存发送失败文件完成。" << endl;
}
