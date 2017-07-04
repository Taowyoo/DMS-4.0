#ifndef _FILEDAO_H
#define _FILEDAO_H
using namespace std;
#include <fstream>
#include "logdao.h"
#include "data.h"

class FileDao : public LogDao
{
    private:
        ofstream m_ofs;
    public:
        FileDao(const string& path) throw (DBException);
        ~FileDao();
        void insert(const MLogRec& log)throw ();
};

#endif //_FILEDAO_H
