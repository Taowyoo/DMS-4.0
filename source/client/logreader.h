#ifndef _LOGREADER_H
#define _LOGREADER_H
#include <string>
#include <list>
#include "data.h"
#include "except.h"
using namespace std;

class LogReader
{
    public:
	LogReader (const string& logFile,
	const string& loginsFile) ;

    list<MLogRec>& readLog (void)throw(ReadException);
	 //string getm_logFile();
	 //void setm_logFile(string logFile);
	 // string getm_loginsFile();
	 //void setm_loginsFile(string loginsFile);
     	 //string setm_backupFile();
	 //void setm_backupFile(string backupFile);
         void print();
private:
    string m_logFile;//ÈÕÖŸŒÇÂŒÎÄŒþÃû
    string m_loginsFile;//ÎŽÆ¥ÅäŒÇÂŒÎÄŒþÃû
    string m_backupFile;//±ž·ÝÎÄŒþÃû
    list<LogRec> m_logins;//µÇÈëŒÇÂŒ
    list<LogRec> m_logouts;//µÇ³öŒÇÂŒ
    list<MLogRec> m_logs;//Æ¥ÅäÈÕÖŸŒÇÂŒ
	void backup (void)throw (BackupException);
	void readLoginsFile (void)throw (ReadException);
	void readBackupFile (void)throw (ReadException);
	void match(void);
	void saveLoginsFile(void)throw (SaveException);
};
#endif
