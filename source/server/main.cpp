#include <QApplication>
#include <iostream>

#include "filedao.h"
#include "mysqldao.h"
#include "server.h"
//#include "clverify.h"
//#include<Conformity_Adress.h>
#include<string.h>
#include "mainwindow.h"
#include <unistd.h>
#include "login.h"
#include <QFile>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFile file(":/qss/qss/metrol.qss");//路径为应用程序所在目录开始
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);

    if (argc == 1)
    {
        login lg;
        qApp->setStyleSheet(styleSheet);
        //登录验证
        if(lg.exec() == QDialog::Accepted)
        {


            try {
                //FileDao dao ("./mlr.db");
                MysqlDao dao;
                Server *server = new Server(dao, "127.0.0.1", 2015, 2010);
                server->dataMine();
                MainWindow w;
                w.show();
                return a.exec();
            }
            catch (ServerException& ex) {
                cout << ex.what () << endl;
                return -1;
            }

        }
    }
    else
    {
        qApp->setStyleSheet(styleSheet);
        MainWindow w;
        w.show();
        return a.exec();
    }

    return a.exec();
}

