#ifndef LOGQUEUE_H
#define LOGQUEUE_H
#include <pthread.h>
#include <list>
#include "data.h"
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#define MAX_SIZE 1024
using namespace std;
#define errExitEN(en, msg) \
            do { errno = en; perror(msg); exit(EXIT_FAILURE); \
        } while (0)

class LogQueue
{
public:
	// 构造函数
	LogQueue (void);
	// 压入日志记录
	LogQueue& operator<< (
		const MLogRec& log);
	// 弹出日志记录
	LogQueue& operator>> (MLogRec& log);
	virtual ~LogQueue();
private:
	pthread_mutex_t m_mutex; // 同步互斥量
	pthread_cond_t  m_cond;  // 同步条件量
	list<MLogRec>   m_logs;  // 日志记录集
};

//extern LogQueue logqueue;
#endif // _LOGQUEUE_H

