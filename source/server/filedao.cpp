#include <iostream>
#include <fstream>
#include "data.h"
#include "logdao.h"
#include "filedao.h"
using namespace std;

//构造函数
FileDao::FileDao(const string& path) throw (DBException){
    //打开数据库文件
    cout<<"打开数据库文件开始..."<<endl;
    m_ofs.open(path.c_str(),ios::app);
    if(!m_ofs) throw DBException("打开数据库文件失败！");
    else
        cout<<"打开数据库文件完成。"<<endl;
}

//插入数据
void FileDao::insert(const MLogRec& log)throw ()
{
    cout<<"插入数据开始..."<<endl;
    m_ofs<<log.logname<<" "<<log.logpip<<" "<<log.logpid<<" "<<log.logtimein<<" "<<log.logtimeout<<" "<<log.timelong<<endl;
    cout<<"插入数据完成。"<<endl;
}

//析构函数
FileDao::~FileDao()
{
    cout<<"关闭数据库文件开始..."<<endl;
    m_ofs.close();
    cout<<"关闭数据库文件完成。"<<endl;
}
