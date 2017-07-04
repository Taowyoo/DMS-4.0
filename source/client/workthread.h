#ifndef _WORKTHREAD_H
#define _WORKTHREAD_H

#include <QThread>
#include <QString>
#include <string>
#include "except.h"
#include "socketsender.h"
#include "client.h"
#include "data.h"

class WorkThread:public QThread
{
    Q_OBJECT
public:
    WorkThread(){}

    void run(void);
    void update(MLogRec log);
    ~WorkThread(){}
signals:
    void updates(MLogRec log);
};

#endif // _WORKTHREAD_H
