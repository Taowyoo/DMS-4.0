//声明mysql数据访问对象类
#ifndef _MYSQLDAO_H
#define _MYSQLDAO_H

#include "logdao.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "data.h"
#include "sexcept.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class MysqlDao :public LogDao
{
public:
    MysqlDao();
    ~MysqlDao();
    string getStringFromLong(long);
    string getStringFromTime(long);
    void insert(const MLogRec& log) throw(DBException);
    //int select(const User& user) throw(DBException);
    string getYear(long long_time);
    string getMonth(long long_time);
    string getDay(long long_time);
    void remove()throw(DBException);
    int select(const User& user) throw(DBException);
    void userinsert(const User& user) throw(DBException);
//void select_userfee(string username) throw(DBException);
    void select_day(string str1,string str2,string str3) throw(DBException);
    void select_month(string str1,string str2) throw(DBException);
    void select_year(string str1) throw(DBException);
    void addTable1(string str1,string str2) throw(DBException);
    void addTable2(string str1,string str2) throw(DBException);
    map<string,table> deal(string str,float price=0.01);
private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *pstmt;
    //sql::Statement *state;
    //sql::ResultSet *result;
};

extern int rows;
#endif //_MYSQLDAO_H
