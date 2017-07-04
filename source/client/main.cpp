#include "clientdlg.h"
#include "login.h"
#include "uregister.h"
#include <QApplication>
#include "socketsender.h"
#include <iostream>
#include <QFile>

//#define IP_ADDRESS "127.0.0.1"
#define IP_ADDRESS "123.206.188.153"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc != 1) {
        try {
            LogReader reader ("./wtmpx",
                              "./logins.dat");
            //			ConsoleSender sender;
            SocketSender sender (IP_ADDRESS,
                                 2015, "./fail.dat",NULL);
            Client client (reader, sender);
            client.dataMine ();
        }
        catch (ClientException& ex) {
            cout << ex.what () << endl;
            return -1;
        }
    }
    else{

        clientdlg cdlg;
        cdlg.ipAddress = IP_ADDRESS;
        loginwindow logui;
        logui.ipAddress = IP_ADDRESS;
        QFile file(":/qss/qss/metrol.qss");//路径为应用程序所在目录开始
        file.open(QFile::ReadOnly);
        QString styleSheet = QString::fromLatin1(file.readAll());
        qApp->setStyleSheet(styleSheet);

        while(1)
        {
            if(logui.exec()==QDialog::Accepted)
            {
                //ureg.show();

                cdlg.show();
                return a.exec();
            }
            //        else if(logui.exec()==QDialog::Accepted)
            //        {
            //            ureg.show();
            //            //return a.exec();
            //        }
            //        else
            //          return 0;
        }
    }
}


