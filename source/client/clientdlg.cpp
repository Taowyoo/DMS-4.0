#include "clientdlg.h"
#include "ui_clientdlg.h"
#include "login.h"
#include "data.h"
#include "client.h"
#include "logreader.h"
#include "socketsender.h"
#include <iomanip>
#include <time.h>
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>
#include <QObject>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <QDesktopWidget>



using namespace std;

clientdlg::clientdlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientdlg),
    count(0)
{
    ui->setupUi(this);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    ui->mainToolBar->hide();

    styleSheetEditor = new StyleSheetEditor(this);

    startAction = new QAction(QIcon(), tr("start"), this);
    startAction->setIcon(QIcon(":/images/start"));
    startAction->setStatusTip(tr("start send!"));

    logoutAction = new QAction(QIcon(), tr("logout"), this);
    logoutAction->setIcon(QIcon(":/images/logout"));
    logoutAction->setStatusTip(tr("logout!"));

    clearAction = new QAction(QIcon(), tr("clear"), this);
    clearAction->setIcon(QIcon(":/images/clear"));
    clearAction->setStatusTip(tr("clear table!"));

    editStyleAction = new QAction(tr("changeStyle"),this);
    editStyleAction->setIcon(QIcon(":/images/changestyle"));
    editStyleAction->setStatusTip(tr("change the style of skin!"));

    aboutAction = new QAction(tr("About"),this);
    aboutAction->setIcon(QIcon(":/images/about"));
    aboutAction->setStatusTip(tr("Information about this program!"));

    QMenu *menu = menuBar()->addMenu(tr("Operation"));
    menu->addAction(startAction);
    menu->addAction(clearAction);
    menu->addAction(logoutAction);
    menu->addAction(editStyleAction);
    QMenu *help = menuBar()->addMenu(tr("Help"));
    help->addAction(aboutAction);

//    QToolBar *toolBar = addToolBar(tr("tool"));
//    toolBar->addAction(startAction);
//    toolBar->addAction(logoutAction);

//    toolBar->addAction(clearAction);

    connect(startAction, &QAction::triggered,
            this,&clientdlg::startsend);
    connect(logoutAction,&QAction::triggered,
            this, &clientdlg::logout);
    connect(clearAction,&QAction::triggered,
            this,&clientdlg::cleartable);
    connect(editStyleAction,&QAction::triggered,
            this,&clientdlg::editStyleAction_triggered);
    connect(aboutAction,&QAction::triggered,
            this,&clientdlg::aboutAction_triggered);
    //connect(tsendAction,&QAction::triggered,
            //this,&clientdlg::timesend);

   // connect(openAction, &QAction::triggered, this, add);


}

void clientdlg::startsend()
{
    //m_work->start();//start or create workthread
    LogReader reader("./wtmpx","./logins.dat");
    SocketSender sender(ipAddress,2015,"./fail.dat",NULL);
    Client client(reader,sender);
    list<MLogRec> mlog;
    mlog=client.dataMine();

    //ui->table->setRowCount(mlog.size());
    ui->table->setColumnCount(6);
    ui->table->setRowCount(mlog.size());

    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->table->verticalHeader()->setVisible(true);
    ui->table->setShowGrid(true);
    //ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条

    ui->table->setColumnWidth(0,80);
    ui->table->setColumnWidth(1,124);
    ui->table->setColumnWidth(2,82);
    ui->table->setColumnWidth(3,75);
    ui->table->setColumnWidth(4,150);
    ui->table->setColumnWidth(5,150);
    //tableWidget->setRowHeight(3,60); //指定行列大小

    QStringList header;
    //ui->table->set
    header<<"登录用户名"<<"登录IP"<<"登录进程号"<<"登录时长"<<"登入时刻"<<"登出时刻";
    ui->table->setHorizontalHeaderLabels(header);

    int j=0;
    for( list<MLogRec>::iterator it=mlog.begin();it!=mlog.end();++it,++j)
    {
    if(j%2)

    {
    QTableWidgetItem *item = new QTableWidgetItem((QString)it->logname);
    //item->setBackground(QBrush(QColor(255,255,255)));
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    ui->table->setItem(j, 0, item);

    QTableWidgetItem *item1 = new QTableWidgetItem((QString)it->logpip);
    //item1->setBackground(QBrush(QColor(255,255,255)));
    item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
    ui->table->setItem(j, 1, item1);

    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(it->logpid));
    //item2->setBackground(QBrush(QColor(255,255,255)));
    item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
    ui->table->setItem(j, 2, item2);

    string time=gettimelong(it->timelong);
    QTableWidgetItem *item3 = new QTableWidgetItem(stoq(time));
    //item3->setBackground(QBrush(QColor(255,255,255)));
    item->setFlags(item3->flags() & (~Qt::ItemIsEditable));
    ui->table->setItem(j, 3, item3);

    string str=getStringFromLong(it->logtimein);
    QTableWidgetItem *item4 = new QTableWidgetItem(stoq(str));
    //item4->setBackground(QBrush(QColor(255,255,255)));
    item4->setFlags(item4->flags() & (~Qt::ItemIsEditable));
    ui->table->setItem(j, 4, item4);

    string str1=getStringFromLong(it->logtimeout);
    QTableWidgetItem *item5 = new QTableWidgetItem(stoq(str1));
    //item5->setBackground(QBrush(QColor(255,255,255)));
    item5->setFlags(item5->flags() & (~Qt::ItemIsEditable));
    ui->table->setItem(j, 5, item5);
    }
    else

        {
        QTableWidgetItem *item = new QTableWidgetItem((QString)it->logname);
        //item->setBackground(QBrush(QColor(224,238,224)));
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->table->setItem(j, 0, item);

        QTableWidgetItem *item1 = new QTableWidgetItem((QString)it->logpip);
        //item1->setBackground(QBrush(QColor(224,238,224)));
        item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
        ui->table->setItem(j, 1, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(it->logpid));
        //item2->setBackground(QBrush(QColor(224,238,224)));
        item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
        ui->table->setItem(j, 2, item2);

        string time=gettimelong(it->timelong);
        QTableWidgetItem *item3 = new QTableWidgetItem(stoq(time));
        //item3->setBackground(QBrush(QColor(224,238,224)));
        item->setFlags(item3->flags() & (~Qt::ItemIsEditable));
        ui->table->setItem(j, 3, item3);

        string str=getStringFromLong(it->logtimein);
        QTableWidgetItem *item4 = new QTableWidgetItem(stoq(str));
        //item4->setBackground(QBrush(QColor(224,238,224)));
        item4->setFlags(item4->flags() & (~Qt::ItemIsEditable));
        ui->table->setItem(j, 4, item4);

        string str1=getStringFromLong(it->logtimeout);
        QTableWidgetItem *item5 = new QTableWidgetItem(stoq(str1));
        //item5->setBackground(QBrush(QColor(224,238,224)));
        item5->setFlags(item5->flags() & (~Qt::ItemIsEditable));
        ui->table->setItem(j, 5, item5);


        }
    }

}
string clientdlg::gettimelong(long long_time)
{
     std::ostringstream ostr;
     int hour,min,sec,temp;
     hour = long_time/3600;
     temp = long_time%3600;
     min = temp/60;
     sec = temp%60;
     ostr<<hour<<":"<<min<<":"<<sec;
     return ostr.str();
}

string clientdlg::getStringFromLong(long long_time)
{
    std::ostringstream ostr;//生成未匹配文件名
    //int hour,min,sec,temp;

    time_t now_time = long_time;
    struct tm *now_tm;
    now_tm = localtime(&now_time);
            //now_tm->tm_year+1900,now_tm->tm_mon+1,now_tm->tm_mday,
            //now_tm->tm_hour,now_tm->tm_min,now_tm->tm_sec);
           //ostr<<setfill('0')//空位填充
           ostr<<setw(4)<<now_tm->tm_year+1900<<"-"
           <<setw(2)<<now_tm->tm_mon+1<<"-"
           <<setw(2)<<now_tm->tm_mday<<"  "
           <<setw(2)<<now_tm->tm_hour<<":"
           <<setw(2)<<now_tm->tm_min<<":"
           <<setw(2)<<now_tm->tm_sec;

    return ostr.str();
}
string clientdlg::qtos(const QString &s)
{
    return string((const char *)s.toLocal8Bit());
}

QString clientdlg::stoq(const string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}


void clientdlg::updatetable(MLogRec log)
{
    int row=ui->table->rowCount();
    ui->table->insertRow(row);
    if(count%2)
    {
        //rol!!!
        for(int i=0;i!=6;i++)
        {
        QTableWidgetItem *item = new QTableWidgetItem(log.logname);
        //item->setBackground(QBrush(QColor(255,255,255)));
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->table->setItem(count, i, item);
        }
    }
    else
    {
        for(int i=0;i!=6;i++)
        {
        QTableWidgetItem *item = new QTableWidgetItem(log.logname);
        //item->setBackground(QBrush(QColor(224,238,224)));
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        ui->table->setItem(count, i, item);
        }
    }

    ++count;
}
void clientdlg::logout()
{
    exit(0);
    //loginwindow logui;
    //logui.show();
    //logui.exec();
}

void clientdlg::cleartable()
{
    count=0;
    for(int i = ui->table->rowCount()-1;i>=0 ;--i)
       {
           ui->table->removeRow(i);
       }
}
void clientdlg::editStyleAction_triggered()
{
    styleSheetEditor->show();
    styleSheetEditor->activateWindow();
}

void clientdlg::aboutAction_triggered()
{
    QMessageBox::about(this, tr("About the client of DMS system"),
        tr("The <b>DMS System Client</b> give the function of login, register,sending<br />"
           "and checking logs.<br />"
           "The source codes are shared on <a href=\"https://coding.net/u/NickelCAo/p/DMS-4.0/git\">NickelCAo/DMS-4.0</a> on Coding.net.<br />"
           "Created by No.5 Programing Group."
           ));
}
clientdlg::~clientdlg()
{
    delete m_work;
    delete ui;
}
