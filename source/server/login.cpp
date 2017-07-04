#include "login.h"
#include "ui_login.h"
#include "QMessageBox"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    uid="root";
    upassword="123456";

    connect(ui->button1,SIGNAL(clicked()),
            this,SLOT(check()));
    connect(ui->button2,SIGNAL(clicked()),
            this,SLOT(reset()));

}
void login::reset()
{
    ui->lineEdit_2->clear();
    ui->lineEdit->clear();
}

void login::check()
{
    QString id=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    if((id==uid)&&(password==upassword))
    {

        QDialog::accept();
        hide();

    }
    else
        QMessageBox::information(this, tr("Information"), tr("login failed,please enter again!"));


}

login::~login()
{
    delete ui;
}
