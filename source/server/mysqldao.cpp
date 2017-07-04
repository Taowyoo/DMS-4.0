//实现mysql数据访问对象类
#include "mysqldao.h"
#include "data.h"
#include <cstdlib>
#include <string.h>
//#include <list>
#include <string.h>
//#include <vector>
#include <map>

using namespace std;

int rows=0;
//类实现
//构造函数
MysqlDao::MysqlDao()
{
    driver = get_driver_instance();
    con = driver->connect("tcp://localhost:3306","root","123456");
    con->setSchema("dms");	//connect to the dms database
    //state=con.CreatStatement();
    cout<<"mysql connected"<<endl;
    pstmt=con->prepareStatement("create table IF NOT EXISTS mlogrec (logname char(32),logpip char(32),logpid int,logtimein char(32),logtimeout char(32),timelong char(32),year char(4),month char(2),day char(2),second int)");
    bool is_success = pstmt->executeUpdate();
    pstmt=con->prepareStatement("create table IF NOT EXISTS users(username char(32),userpassword char(32),useremail char(32),userphone char(32))");
    is_success = pstmt->executeUpdate();
}

std::string MysqlDao::getStringFromLong(long long_time)
{
    time_t now_time = long_time;
    struct tm *now_tm;
    now_tm = localtime(&now_time);
    char arr[20];
    sprintf(arr,"%04d-%02d-%02d %02d:%02d:%02d",now_tm->tm_year+1900,now_tm->tm_mon+1,now_tm->tm_mday,now_tm->tm_hour,now_tm->tm_min,now_tm->tm_sec);
    string str(arr);
    return str;
}

std::string MysqlDao::getYear(long long_time)
{
    time_t now_time = long_time;
    struct tm *now_tm;
    now_tm = localtime(&now_time);
    char arr[5];
    sprintf(arr,"%04d",now_tm->tm_year+1900);
    string str(arr);
    return str;
}

std::string MysqlDao::getMonth(long long_time)
{
    time_t now_time = long_time;
    struct tm *now_tm;
    now_tm = localtime(&now_time);
    char arr[5];
    sprintf(arr,"%02d",now_tm->tm_mon+1);
    string str(arr);
    return str;
}

std::string MysqlDao::getDay(long long_time)
{
    time_t now_time = long_time;
    struct tm *now_tm;
    now_tm = localtime(&now_time);
    char arr[5];
    sprintf(arr,"%02d",now_tm->tm_mday);
    string str(arr);
    return str;
}

std::string MysqlDao::getStringFromTime(long long_time)
{
    int hour,min,sec,temp;
    hour = long_time/3600;
    temp = long_time%3600;
    min = temp/60;
    sec = temp%60;
    char arr[10];
    sprintf(arr,"%02d:%02d:%02d",hour,min,sec);
    string str(arr);
    return str;
}

void MysqlDao::remove()throw(DBException)
{	
    //cout<<"sssss1111111111111111"<<endl;
    pstmt = con->prepareStatement("delete from mlogrec");
    bool is_success = pstmt->executeUpdate();
    //cout<<"sssss22222222222222222"<<endl;
}

void MysqlDao::insert(const MLogRec& log) throw(DBException)
{
    pstmt = con->prepareStatement("insert into mlogrec (logname,logpip,logpid,logtimein,logtimeout,timelong,year,month,day,second) values(?,?,?,?,?,?,?,?,?,?)");
    //pstmt->setString(1,"admin");
    pstmt->setString(1,log.logname);
    pstmt->setString(2,log.logpip);
    pstmt->setInt(3,log.logpid);
    pstmt->setString(4,getStringFromLong(log.logtimein));
    pstmt->setString(5,getStringFromLong(log.logtimeout));
    pstmt->setString(6,getStringFromTime(log.timelong));
    pstmt->setString(7,getYear(log.logtimeout));
    pstmt->setString(8,getMonth(log.logtimeout));
    pstmt->setString(9,getDay(log.logtimeout));
    pstmt->setInt(10,log.timelong);
    bool is_success = pstmt->executeUpdate();
    
    if(!is_success)
        throw DBException("MysqlDao::insert failed!");

    rows++;
}

int MysqlDao::select(const User& user) throw(DBException)
{
    sql::ResultSet *result;
    pstmt = con->prepareStatement("select userpassword from users where username=?;");
    pstmt -> setString(1,user.name);
    cout<<"在select中  "<<user.name<<endl;
    try{
        result=pstmt->executeQuery();
        result->next();
        cout<< result->getString(1).c_str()<<endl;
        if(strcmp(result->getString(1).c_str(),user.password)==0)//第二列password列
        {	cout<<result->getString(1).c_str()<<"  return 2  /验证成功"<<endl;
            //select_userfee(user.name);
            return 2;//验证成功
        }
        else
            return 1;//密码错误
    }catch(exception e)
    {return 0;//用户名不存在
    }
}
//查询用户年金额
/*
string MysqlDao::select_userfee(string username) throw(DBException)
{
    string usercost;
    pstmt = con->prepareStatement("select cost from form20160000 where logname=?");
     pstmt->setString(1,username);
     sql::ResultSet *rs = pstmt->executeQuery();
     rs->next();
     usercost=rs->getString("cost");
     return usercost;
}*/

void MysqlDao::userinsert(const User& user) throw(DBException)
{
    pstmt = con->prepareStatement("insert into users (username,userpassword,useremail,userphone) values(?,?,?,?)");
    //pstmt->setString(1,"admin");
    pstmt->setString(1,user.name);
    pstmt->setString(2,user.password);
    pstmt->setString(3,user.email);
    pstmt->setString(4,user.phone);
    bool is_success = pstmt->executeUpdate();
    if(is_success)
        cout << "insert success!" << endl;
    else
        cout << "insert fail!" << endl;
}
//查询数据
void MysqlDao::select_day(string str1,string str2,string str3) throw(DBException)
{   
    pstmt = con->prepareStatement("select * from mlogrec where year=? and month=? and day=?");
    pstmt->setString(1,str1);
    pstmt->setString(2,str2);
    pstmt->setString(3,str3);
    sql::ResultSet *rs = pstmt->executeQuery();
    cout<<"okkkkkk"<<endl;
    string str=str1+str2+str3;
    while(rs->next())
    {
        cout<<"ok"<<endl;
        pstmt = con->prepareStatement("insert into table"+str+"(logname,timelong,second) values(?,?,?)");
        //pstmt->setString(1,"admin");
        pstmt->setString(1,rs->getString("logname"));
        pstmt->setString(2,rs->getString("timelong"));
        pstmt->setInt(3,rs->getInt("second"));
        cout<<"select finish"<<endl;
        bool is_success = pstmt->executeUpdate();
        if(is_success)
            cout << "select  success!" << endl;
        else
            cout << "select fail!" << endl;}
    rs->close();
    pstmt->close();


}
void MysqlDao::select_month(string str1,string str2) throw(DBException)
{
    pstmt = con->prepareStatement("select * from mlogrec where year=? and month=?");
    pstmt->setString(1,str1);
    pstmt->setString(2,str2);
    sql::ResultSet *rs = pstmt->executeQuery();
    string str=str1+str2;
    while(rs->next())
    {pstmt = con->prepareStatement("insert into table"+str+" (logname,timelong,second) values(?,?,?)");
        //pstmt->setString(1,"admin");
        pstmt->setString(1,rs->getString("logName"));
        pstmt->setString(2,rs->getString("timelong"));
        pstmt->setInt(3,rs->getInt("second"));
        bool is_success = pstmt->executeUpdate();
        if(is_success)
            cout << "select  success!" << endl;
        else
            cout << "select  fail!" << endl;}
    rs->close();
    pstmt->close();



}
void MysqlDao::select_year(string str1) throw(DBException)
{
    pstmt = con->prepareStatement("select * from mlogrec where year=?");
    pstmt->setString(1,str1);
    sql::ResultSet *rs = pstmt->executeQuery();
    string str=str1;
    while(rs->next())
    {pstmt = con->prepareStatement("insert into table"+str+" (logname,timelong,second) values(?,?,?)");
        //pstmt->setString(1,"admin");
        pstmt->setString(1,rs->getString("logName"));
        pstmt->setString(2,rs->getString("timelong"));
        pstmt->setInt(3,rs->getInt("second"));
        bool is_success = pstmt->executeUpdate();
        if(is_success)
            cout << "select  success!" << endl;
        else
            cout << "select  fail!" << endl;}
    rs->close();
    pstmt->close();
}


void MysqlDao::addTable1(string str1,string str2) throw(DBException)
{
    string sql = "DROP table IF EXISTS ";
    sql += str1;
    sql += str2;
    pstmt = con->prepareStatement(sql);
        try{
            pstmt->executeUpdate();
        }
        catch(DBException& e){
            cout<<("执行sql语句失败");
        }
    sql = "CREATE table IF NOT EXISTS ";
    sql += str1;
    sql += str2;
    sql += " (logname varchar(20),timelong varchar(20),second int)";
    cout<<sql<<endl;
    pstmt = con->prepareStatement(sql);
    try{
        pstmt->executeUpdate();
    }
    catch(DBException& e){
        cout<<("执行sql语句失败");
    }

}

void MysqlDao::addTable2(string str1,string str2) throw(DBException)
{
    string sql = "CREATE table IF NOT EXISTS ";
    sql += str1;
    sql += str2;
    sql += " (logname varchar(20),timelong varchar(20),cost float,times int)";
    cout<<sql<<endl;
    pstmt = con->prepareStatement(sql);
    try{
        pstmt->executeUpdate();
    }
    catch(DBException& e){
        cout<<("执行sql语句失败");
    }

}

map<string,table> MysqlDao::deal(string str,float price)
{
    //int i=0,j=0;
    string name;//??????
    long second;
    string timelong;
    float cost;
    unsigned int times = 0;
    //vector<table> tbs;
    //list<table> tbs;

    table t;
    map<string,table> mt;

    //tbs.push_front(t);

    pstmt = con->prepareStatement("select * from table"+str);
    sql::ResultSet *rs = pstmt->executeQuery();

    while(rs->next())
    {

        name=rs->getString(1);
        second=rs->getInt(3);
        timelong=rs->getString(2);
        cost=(second*price);
        //times = rs->
        times=0;
        map<string,table>::iterator it=mt.find(name);
        if(it != mt.end())
        {
            it->second.second += second;
            it->second.timelong=getStringFromTime(it->second.second);
            it->second.cost+=cost;
            it->second.times+=1;
        }
        else
        {
            //strcpy(t.name,name);
            //strcpy(t.timelong,timelong);
            t.name=name;
            t.timelong=timelong;
            t.cost=cost;
            t.second=second;
            t.times=times;
            mt.insert(make_pair(name,t));
        }
    }

    for(map<string,table>::iterator it=mt.begin();it!=mt.end();++it)
    {
        pstmt = con->prepareStatement("insert into form"+str+" (logname,timelong,cost,times) values(?,?,?,?)");
        pstmt->setString(1,it->second.name);
        pstmt->setString(2,it->second.timelong);
        pstmt->setDouble(3,it->second.cost);
        pstmt->setInt(4,it->second.times);
        bool is_success = pstmt->executeUpdate();
        if(is_success)
            cout << "select  success!" << endl;
        else
            cout << "select  fail!" << endl;
    }
    rs->close();
    pstmt->close();

    return mt;
}
/*
int MysqlDao::select(const User& user) throw(DBException)
{	
    ResultSet result;
    pstmt = con->prepareStatement("select name,password from user where name='?'");
    pstmt -> setString(1,user.name);
    try{
    result = pstmt->executeQuery();
    }catch(SQLException)
    {return 0;//用户名不存在
    }
    result.getString(name);
    if(strcmp(result.getString(password),user.password)==0)
    return 2;//验证成功
    else
    return 1;//密码错误
}
*/
MysqlDao::~MysqlDao()
{
    if(pstmt != NULL)
        delete pstmt;
    con->close();
    delete con;
    cout<<"total:"<<rows<<endl;
}
