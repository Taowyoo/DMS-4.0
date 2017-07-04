#ifndef CONFORMITY_ADRESS_H
#define CONFORMITY_ADRESS_H
#include<map>
#include<iostream>
#include<mysqldao.h>
#include"data.h"
using namespace std;
class Conformity_Adress
{
MysqlDao  m_dao;
public:
//    vector<MatchedRecord> conformity(vector<MatchedRecord> mrs);

//     vector<MatchedRecord> conformity(vector<MatchedRecord> mrs1,vector<MatchedRecord> mrs2);
    map<string,table> dayConformity(string str1,string str2,string str3,float price=0.01);
    map<string,table> monthConformity(string str1,string str2,float price=0.01);

    map<string,table> yearConformity(string str1,float price=0.01);

};

#endif // CONFORMITY_ADRESS_H
