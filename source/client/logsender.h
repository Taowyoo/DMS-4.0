// ÈÕÖŸ·¢ËÍÆ÷œÓ¿ÚÀà
#ifndef _LOGSENDER_H
#define _LOGSENDER_H
#include <list>
using namespace std;
#include "data.h"
#include "except.h"
// ÈÕÖŸ·¢ËÍÆ÷œÓ¿ÚÀà
class LogSender {
public:

    //¹¹Ôìº¯Êý
    virtual void sendLog (list<MLogRec>& logs)
throw (SendException) = 0;
    //Îö¹¹º¯Êý
    virtual ~LogSender (void) {}
};
#endif // _LOGSENDER_H
