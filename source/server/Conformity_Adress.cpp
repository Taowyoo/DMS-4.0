
#include <iostream>
#include "Conformity_Adress.h"
#include "data.h"
#include <map>
using namespace std;
//Conformity_Adress::Conformity_Adress (){}
// 数据整合

//vector<MatchedRecord> Conformity_Adress:: conformity(vector<MatchedRecord> mrs)
//{
//    //获得没有重复登录名的登录数据的集合
//    for(int i=0;i<mrs.size();i++)
//    {

//       for(int j=i;j<mrs.size();j++)
//         //如果登录名字相同，id不同，就执行if里的语句
//        {
//            if(mrs.get(i).getLogName()==(mrs.get(j).getLogName())&&mrs.get(i).getLogip()==(mrs.get(j).getLogip()))
//            {mrs.get(i).setTimeLong( mrs.get(i).getTimeLong()+mrs.get(i).getgetTimeLong());//登录时长累加
//             mrs.remove(j);//把登录时长累加到i里后，删除j数据
//             j--;//删除数据后，j要自减
//             }
//         }
//    }
//    return mrs;
//}

//vector<MatchedRecord> Conformity_Adress:: conformity(vector<MatchedRecord> mrs1,vector<MatchedRecord> mrs2)
//{
//    //获得没有重复登录名的登录数据的集合
//    for(int i=0;i<mrs1.size();i++)
//    {

//       for(int j=0;j<mrs2.size();j++)
//         //如果登录名字相同，id不同，就执行if里的语句
//        {
//            if(mrs1.get(i).getLogName()==(mrs1.get(j).getLogName())&&mrs1.get(i).getLogip()==(mrs2.get(j).getLogip()))
//            {mrs.get(i).setDuration( mrs.get(i).getDuration()+mrs.get(i).getDuration());//登录时长累加
//             mrs2.remove(j);//把登录时长累加到i里后，删除j数据
//             j--;//删除数据后，j要自减
//             continue;
//             }
//         }
//    }
//    if(mrs2.size()!=0)
//    {
//        for(int i=0;i<mrs2.size();i++)
//            mrs1.add(mrs2.get(i));
//    }
//    return mrs1;
//}

map<string,table> Conformity_Adress::dayConformity(string str1,string str2,string str3,float price)
{
    // if(cexist())
    //{
    // ResultSet mrs=Conformity_Adress.conformity(mrs1);
    //保存获得的集合，形成日报表
    map<string,table>mt;
    try{
        string str=str1+str2+str3;
        m_dao.addTable1("table",str);
        m_dao.select_day(str1,str2,str3);
        m_dao.addTable2("form",str);
        mt=m_dao.deal(str,price);
    }catch(ServerException e){
        cout<<e.what()<<endl;
    }

    // }
    return mt;
}


map<string,table> Conformity_Adress::monthConformity(string str1,string str2,float price)
{
    // if(cexist())
    // { cout<<("日整合成功");}

    //ResultSet mrs=Conformity_Adress.conformity(mrs1);
    //保存获得的集合，形成日报表
    map<string,table> mt;
    try{
        string str=str1+str2;
        m_dao.addTable1("table",str);
        m_dao.select_month(str1,str2);
        m_dao.addTable2("form",str);
        mt=m_dao.deal(str,price);
    }catch(ServerException e){
        cout<<e.what()<<endl;
    }
    return mt;
}

map<string,table> Conformity_Adress::yearConformity(string str1,float price)
{
    // if(cexist())
    // {

    //ResultSet mrs=Conformity_Adress.conformity(mrs1);
    //保存获得的集合，形成日报表
    map<string,table> mt;
    try{
        string str=str1;
        m_dao.addTable1("table",str);
        m_dao.select_year(str1);
        m_dao.addTable2("form",str);
        mt=m_dao.deal(str,price);
    }catch(ServerException e){
        cout<<e.what()<<endl;
    }
    return mt;
    // }
}
