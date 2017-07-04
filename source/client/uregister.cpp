#include "uregister.h"
#include "ui_uregister.h"
#include "clogin.h"
#include "login.h"
#include <QMessageBox>

#include <iostream>

uregister::uregister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uregister)
{
    ui->setupUi(this);
    ui->reset->hide();
    //connect(ui->login,&QPushButton::clicked , this, &loginwindow::islogin);
    connect(ui->submit,&QPushButton::clicked,this,&uregister::usubmit);
    connect(ui->reset,&QPushButton::clicked,this,&uregister::ureset);
}
void uregister::ureset()
{
    ui->mailEdit->setText(NULL);
    ui->phoneEdit->setText(NULL);
    ui->pwEdit->setText(NULL);
    ui->repwEdit->setText(NULL);
    ui->unameEdit->setText(NULL);
}
void uregister::usubmit()
{
    CLogin clogin(ipAddress,2010);
    int compare=QString::compare(ui->pwEdit->text(),ui->repwEdit->text());
    if(compare!=0)
    {
        ui->repwEdit->setText("Confirm password error!!");
    }else
    {
        User user;
        int result1;
        QString name=ui->unameEdit->text();
        QString pw=ui->pwEdit->text();
        QString email=ui->mailEdit->text();
        QString phone=ui->phoneEdit->text();
        strcpy(user.name,name.toLatin1().data());
        strcpy(user.password,pw.toLatin1().data());
        strcpy(user.email,email.toLatin1().data());
        strcpy(user.phone,phone.toLatin1().data());
        //ui->repwEdit->text();

        clogin.usersign(user);

        std::cout<<"uregister::usubmit(): sended user register info!"<<std::endl;

        result1=clogin.csignrecv();
        cout<<"uregister::usubmit(): recvieved user register result!"<<endl;

        if(result1==0)
        {
            QMessageBox::information(this, tr("Information"), tr("register success!"));
            hide();

            //loginwindow log;
            //log.exec();
        }
        else if(result1==1||result1==2)
            QMessageBox::information(this, tr("Information"), tr("the user name has been used!"));
        else
            QMessageBox::information(this, tr("Information"), tr("其他错误！!"));

    }


}

uregister::~uregister()
{


    delete ui;
}
