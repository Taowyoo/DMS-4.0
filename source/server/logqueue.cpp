#include "logqueue.h"
#include <algorithm>
#include <iostream>
//LogQueue logqueue;
LogQueue::LogQueue()
{
    pthread_mutex_init(&m_mutex,NULL);//定义互斥量
    pthread_cond_init(&m_cond,NULL);//定义条件变量
}
//压入
LogQueue& LogQueue::operator<< (
    const MLogRec& log)
{
    pthread_mutex_lock(&m_mutex);
    m_logs.push_front(log);
    pthread_cond_signal(&m_cond);
    pthread_mutex_unlock(&m_mutex);
    return *this;
}
//弹出
LogQueue& LogQueue::operator>> (
    MLogRec& log)
{
pthread_mutex_lock (&m_mutex);
    while (m_logs.size()==0) {
        cout<<"当前列表中无日志记录，阻塞等待"<<endl;
       pthread_cond_wait (&m_cond, &m_mutex);
    }
    log = m_logs.front ();
    m_logs.pop_front ();
    pthread_mutex_unlock (&m_mutex);

    return *this;
}

LogQueue::~LogQueue()
{
    pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
}

