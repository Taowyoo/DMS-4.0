#ifndef _CONSOLESENDER_H
#define _CONSOLESENDER_H
#include <iostream>
#include "logsender.h"
#include "data.h"
// ¿ØÖÆÌšÈÕÖŸ·¢ËÍÆ÷Àà
class ConsoleSender : public LogSender {
public:
    // ·¢ËÍÈÕÖŸ
    void sendLog (list<MLogRec>& logs)
        throw (SendException)
        {
           cout<<"console sender run!"<<endl;
          cout << "·¢ËÍÈÕÖŸ¿ªÊŒ..." << endl;
        // ÀûÓÃµüŽúÆ÷ÊµÏÖlist±éÀú£¬²¢Êä³öÆ¥ÅäÈÕÖŸÐÅÏ¢
        for (list<MLogRec>::iterator it = logs.begin (); it != logs.end (); ++it)
        cout<<it->logname<<" "<<it->logpip<<" "<<it->logpid<<" "<<it->logtimein<<" "<<it->logtimeout<<" "<<it->timelong<<endl;
        cout << "·¢ËÍÈÕÖŸÍê³É¡£" << endl;
        }
    ~ConsoleSender() {}

};
#endif // _CONSOLESENDER_H
