#ifndef _LOGDAO_H
#define _LOGDAO_H
#include "data.h"
#include "sexcept.h"

//LogDao接口
class LogDao
{
    //插入
    public :
    virtual void insert(const MLogRec& log) throw (DBException) = 0;
    virtual void remove() throw (DBException) = 0;
    virtual ~LogDao(){}
};

#endif //_LOGDAO_H
