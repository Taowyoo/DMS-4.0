#ifndef CLOGIN_H
#define CLOGIN_H
#include <string>
#include "data.h"
#include "encrypt.h"
#include "except.h"

using namespace std;
class CLogin
{
public:
    CLogin(const string& ip,short port);
    void cloginsend(const char name[32],const char password[32])throw (SendException);
    //int cloginrecv();
    void usersign(User user)throw (SendException);
    int csignrecv()throw (SendException);
    //int close();
    ~CLogin();

private:
    int clogin_sockfd;

};
#endif // CLOGIN_H
