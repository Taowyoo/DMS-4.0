#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/stat.h>
#include <list>
#include "logreader.h"
#include <arpa/inet.h>

using namespace std;
#define N 1024


LogReader::LogReader (const string& logFile,
                      const string& loginsFile) :
    m_logFile (logFile),
    m_loginsFile (loginsFile) {}
// 读取并返回匹配记录
list<MLogRec>& LogReader::readLog (void)
throw(ReadException)
{
    std::cout << "读取日志开始..." << std::endl;

    try
    {
        backup();           // 备份日志文件
        readLoginsFile();   // 读取登入文件
    cout<<"readlogin:"<<m_logins.size()<<endl;
        readBackupFile();   // 读取备份文件
    cout<<"logins:"<<m_logins.size()<<".  "<<"logouts:"<<m_logouts.size()<<endl;
        //print();
        match();            // 匹配登入登出
    cout<<"matchlogs:"<<m_logs.size()<<endl;
        saveLoginsFile();   // 保存登入文件
    }
    catch(BackupException& ex)
    {
        throw ReadException("备份错误");
    }
    catch (ReadException& ex)
    {
        throw ReadException ("读取错误");
    }
    catch (SaveException& ex)
    {
        throw ReadException ("保存错误");
    }
    catch (...)
    {
        throw ReadException ("未知错误");
    }
    std::cout << "读取日志完成。" << std::endl;

    return m_logs;//匹配成功的记录
}

void LogReader::print()
{
    list<LogRec>::iterator it1;
    cout<<"logins record:"<<endl;
    it1=m_logins.begin();
    for(int i=0;i!=5&&it1!=m_logins.end();++i)
    {
        cout<<it1->logname<<" "<<it1->logpip<<" "<<
            it1->logpid<<" "<<it1->logtime<<endl;
        ++it1;
    }
    cout<<"logouts record:"<<endl;
    it1=m_logouts.begin();
    for(int i=0;i!=5&&it1!=m_logouts.end();++i)
        {
            cout<<it1->logname<<" "<<it1->logpip<<" "<<
            it1->logpid<<" "<<it1->logtime<<endl;
        ++it1;
        }

    //print 5 records to test
}
// 备份日志文件，另存为生成新文件
void LogReader::backup(void)
throw (BackupException)
{
    cout<<"开始备份文件..."<<endl;
    time_t now = time (NULL);
    tm* local = localtime (&now);
    std::ostringstream osfname;//生成未匹配文件名

    osfname<<m_logFile<<"."
           <<setfill('0')//空位填充
           <<setw(4)<<local->tm_year+1900
           <<setw(2)<<local->tm_mon+1
           <<setw(2)<<local->tm_mday
           <<setw(2)<<local->tm_hour
           <<setw(2)<<local->tm_min
           <<setw(2)<<local->tm_sec;

    m_backupFile=osfname.str();
    std::cout<<m_backupFile<<std::endl;
    std::string cmd("./backup.sh");
    cmd+=" ";
    cmd+=m_logFile;
    cmd+=" ";
    cmd+=m_backupFile;//运行shell,传入文件名参数
#ifdef DEBUG
    std::cout<<"备份指令："<<cmd<<std::endl;
#endif
    int status=system(cmd.c_str());//shell,exit返回值
    if(WEXITSTATUS(status)==1)
        throw BackupException("拷贝错误");
    if(WEXITSTATUS(status)==2)
        throw BackupException("清空错误");
    cout<<"备份文件完成。"<<m_backupFile<<endl;
}
// 读取上一轮未匹配的登入记录并存入m_logins中
void LogReader::readLoginsFile (void)
throw (ReadException)
{
    std::cout << "读取登入文件开始..." <<std::endl;

    cout<<m_loginsFile<<endl;

    std::ifstream ifsin;
    ifsin.close();
    ifsin.clear();

    ifsin.open(m_loginsFile.c_str(),std::ios::binary);
    if(!ifsin)
        throw ReadException("打开登入文件失败");

    LogRec log;
    while(ifsin.read((char*) &log,sizeof(LogRec)))
        m_logins.push_back(log);
    if(!ifsin.eof())
        throw ReadException();
    ifsin.close();
    ifsin.clear();

#ifdef _DEBUG
    std::cout << "登入日志记录：" <<
              m_logins.size () << std::endl;
#endif
    std::cout << "读取登入文件完成。" << std::endl;
}
// 读取备份文件，并将登入登出记录分别存到登入登出记录链表中
void LogReader::readBackupFile(void)
    throw (ReadException)
{
    std::cout << "读取备份文件开始..." <<std::endl;
    cout<<m_backupFile<<endl;
    std::ifstream ifsbk;
    ifsbk.close();
    ifsbk.clear();

    ifsbk.open(m_backupFile.c_str(),std::ios::binary);
    if(!ifsbk)
        throw BackupException("打开备份文件失败");
    struct stat st;
    if(stat(m_backupFile.c_str(),&st)==-1)//st文件大小
        throw ReadException("无法获取备份文件大小");
    const int rsize=372;
    int records = st.st_size/rsize;
    for(int i=0;i!=records;++i)
    {
        char  logname[32]; // 登录名
        pid_t pid;         // 登录进程ID
        short type;
        long  logtime;     // 登入登出时间
    //char logip[32];// 登录IP
    short lenh;//length of ut_host


        ifsbk.seekg(i*rsize,std::ios::beg);
        ifsbk.read(logname,32);

        ifsbk.seekg(36,std::ios::cur);
        ifsbk.read((char*)&pid,sizeof(pid));
        pid = ntohl (pid);//Network to Host Long

        ifsbk.read((char*)&type,sizeof(type));
        type = ntohs (type);//Network to Host Short

        ifsbk.seekg(6,std::ios::cur);
        ifsbk.read((char*)&logtime,sizeof(logtime));
        logtime = ntohl (logtime);//Network to Host Long

        ifsbk.seekg(24,std::ios::cur);
        ifsbk.read((char*)&lenh,sizeof(lenh));
        lenh = ntohs (lenh);//"Network to Host Short"

        char logpip[lenh+1];
        ifsbk.read (logpip, lenh);
        logpip[lenh] = '\0';
    //ifsbk.seekg(30,ios::cur);
        //ifsbk.read(logip,32);

        //ifsbk.read(logip,lenh);
        //logip[lenh]='\0';//便于转化成string

        // 登录名以.开头的用户是ssh/telnet
        // 软件建立的伪用户，丢弃之
        if (logname[0] != '.') {
            LogRec log;
            strcpy(log.logname,logname);
            strcpy(log.logpip,logpip);
            log.logtime=logtime;
            log.logpid=pid;

            //登录类型7-登入，8登出
            if(type==7)
                m_logins.push_back(log);
            if(type==8)
                m_logouts.push_back(log);
        }
    }
    ifsbk.close();
    ifsbk.clear();

#ifdef _DEBUG
    std::cout << "登入日志记录："
        << m_logins.size () << std::endl;
    std::cout << "登出日志记录："
        << m_logouts.size () << std::endl;
#endif
    std::cout << "读取备份文件完成。" << std::endl;
}
// 匹配登入登出，根据登录进程号来进行匹配，并将匹配记录存在m_logs成员变量中
void LogReader::match(void)
{
    cout<<"开始匹配日志记录"<<endl;
    list<LogRec>::iterator init;
    list<LogRec>::iterator otit;

    //int i=0;

     for(otit=m_logouts.begin();otit!=m_logouts.end();++otit)
    for(init=m_logins.begin();init!=m_logins.end();++init)
        {
            if(!strcmp(init->logname,otit->logname)
                    && !strcmp(init->logpip,otit->logpip)
                    && init->logpid==otit->logpid)//判断登陆信息是否匹配
            {
                MLogRec log;
                log.timelong=otit->logtime - init->logtime;
                strcpy(log.logname,init->logname);
                strcpy(log.logpip,init->logpip);
                log.logpid=init->logpid;
                log.logtimein = init->logtime;
                log.logtimeout = otit->logtime;

                m_logs.push_back(log);
                init=m_logins.erase(init);//避免迭代器失效
        //otit=m_logouts.erase(otit);
                //--otit;
        //cout<<++i<<" ";
            --init;
        break;
            }
        }

    cout<<"共匹配"<<m_logs.size()<<"条记录，共有"<<m_logins.size()<<"登入记录未被匹配"<<endl;
          //，共有"<<m_logouts.size()<<"登出记录未被匹配"<<endl;
}
// 将匹配失败的日志记录存到m_loginsFile文件中（新建文件）
void LogReader::saveLoginsFile(void)
throw (SaveException)
{
    std::cout << "保存登入文件开始..." << std::endl;

    if(!m_logs.empty())
    {
        std::ofstream ofs;
        ofs.close();
        ofs.clear();
        ofs.open(m_loginsFile.c_str(),std::ios::binary);
        if(!ofs)
            throw SaveException("打开登入文件失败");
        while(!m_logins.empty())
        {
            ofs.write((char*)&m_logins.front(),sizeof(LogRec));
            m_logins.pop_front();
        }
        ofs.close();
        ofs.clear();
    }
    std::cout << "保存登入文件完成。" << std::endl;
}

