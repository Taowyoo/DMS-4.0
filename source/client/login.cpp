#include "login.h"
#include "ui_login.h"
#include "clogin.h"
#include <QMessageBox>
#include <string>
#include <sstream>
#include "uregister.h"
#include "except.h"
#include <iostream>



using namespace std;

loginwindow::loginwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginwindow)//ui(new Ui::clientdlg)
{
    ui->setupUi(this);
    connect(ui->myLogin,&QPushButton::clicked , this, &loginwindow::islogin);
    connect(ui->myRegister,&QPushButton::clicked , this, &loginwindow::lregister);
}

string loginwindow::qtos(QString s)
{
    //return string((char *)s.toLocal8Bit());
    string str = s.toStdString();
    return str;
}
void loginwindow::lregister()
{
    //queyigetiaozhuan registerjiemiande yuju
    hide();
    uregister reg;
    reg.ipAddress = ipAddress;
    reg.exec();

    //QDialog::accept();
}
void loginwindow::islogin()
{
    CLogin clogin(ipAddress,2010);
    string str1=qtos(ui->nameEdit->text());
    string str2=qtos(ui->pswEdit->text());

    try{
        clogin.cloginsend(str1.c_str(),str2.c_str());
    }catch(SendException &e){
        cout<<e.what()<<endl;
    }
    int result;
    try{
        result=clogin.csignrecv();
    }catch(SendException &e){
        cout<<e.what()<<endl;
    }


    cout<<"loginwindow::islogin() result: "<<result<<"\n";
    if(result==0)
        QMessageBox::information(this, tr("Information"), tr("ID不存在!"));
    else if(result==1)
        QMessageBox::information(this, tr("Information"), tr("密码错误!"));
    else if(result==2)
        QDialog::accept();
    else
        QMessageBox::information(this, tr("Information"), tr("其他错误！!"));
    /*
    switch(result){
    case 0://0为ID不存在
    QMessageBox::information(this, tr("Information"), tr("ID不存在!"));
    break;
    case 1://1为密码错误
    QMessageBox::information(this, tr("Information"), tr("密码错误!"));
    break;
    case 2://2为验证成功
    QDialog::accept();
    break;
    default:
    QMessageBox::information(this, tr("Information"), tr("其他错误！!"));
    //cout<<"请重新输入用户名和密码"<<endl;
    }
    */
    /*if(ui->nameEdit->text()=="zhou"&&
            ui->pswEdit->text()=="zhou")
        QDialog::accept();
    else
        QMessageBox::information(this, tr("Information"), tr("login failed,please enter again!"));
*/
}


loginwindow::~loginwindow()
{
    delete ui;
}

void loginwindow::on_myExit_clicked()
{
    exit(0);
}
