#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <map>
#include <QString>
#include <QMessageBox>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_year->setFocus();
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    styleSheetEditor = new StyleSheetEditor(this);

    connect(ui->pushButton_calculate, &QPushButton::clicked,
            this,&MainWindow::printrec);
    connect(ui->pushButton_clear, &QPushButton::clicked,
            this,&MainWindow::clearrec);
    connect(ui->actionChange_skin,&QAction::triggered,
            this,&MainWindow::skinChange);
    connect(ui->actionQuit,&QAction::triggered,
            this,&MainWindow::quitProgram);
    connect(ui->actionAbout,&QAction::triggered,
            this,&MainWindow::aboutInfo);
    connect(ui->pushButton_clear_2, &QPushButton::clicked,
            this,&MainWindow::clearrec2);
    connect(ui->pushButton_search, &QPushButton::clicked,
            this,&MainWindow::searchrec);

}

void MainWindow::printrec()
{

    string str1,str2,str3;

    int mon=ui->comboBox_month->currentIndex();
    int day=ui->comboBox_day->currentIndex();
    string str="00";
    float price=0.001;
    price=ui->lineEdit_charge->text().toDouble();
    if(price== 0  )
        price=0.001;

    //string strp= string((const char *)ui->lineEdit->text().toLocal8Bit());

    str1= string((const char *)ui->lineEdit_year->text().toLocal8Bit());
    if(mon<10)
    {
        str2="0";
        str2+=string((const char *)(QString::number(mon)).toLocal8Bit());
    }
    else
        str2=string((const char *)(QString::number(mon)).toLocal8Bit());
    if(day<10)
    {
        str3="0";
        str3+=string((const char *)(QString::number(day)).toLocal8Bit());
    }
    else
        str3=string((const char *)(QString::number(day)).toLocal8Bit());

    //map<string,table> mt;
    string strDay="32";
    string strMon="13";
    if(str3 != str && str3 != strDay)
    {
        mt=conformity.dayConformity(str1,str2,str3,price);
        cout<<"日整合成功"<<endl;
    }
    else if(str2 != str && str3 != strMon)
    {
        mt=conformity.monthConformity(str1,str2,price);
        cout<<"月整合成功"<<endl;
    }
    else
    {
        mt=conformity.yearConformity(str1,price);
        cout<<"年整合成功"<<endl;
    }


    ui->table_cost->setColumnCount(4);
    ui->table_cost->setRowCount(mt.size());
    //ui->table_cost->setColumnCount(6);
    //ui->table_cost->setRowCount(mlog.size());

    ui->table_cost->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->table_cost->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_cost->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->table_cost->verticalHeader()->setVisible(true);
    ui->table_cost->setShowGrid(true);
    //ui->table_cost->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条

    ui->table_cost->setColumnWidth(0,110);
    ui->table_cost->setColumnWidth(1,110);
    ui->table_cost->setColumnWidth(2,110);
    ui->table_cost->setColumnWidth(3,110);
    //ui->table_cost->setColumnWidth(3,75);
    //ui->table_cost->setColumnWidth(4,150);
    //ui->table_cost->setColumnWidth(5,150);
    //tableWidget->setRowHeight(3,60); //指定行列大小

    QStringList header;
    //ui->table_cost->set
    header<<"User Name"<<"Login Times"<<"Log Timelong"<<"Charge(Yuan)";
    ui->table_cost->setHorizontalHeaderLabels(header);

    int j=0;
    for( map<string,table> ::iterator it=mt.begin();it!=mt.end();++it,++j)
    {
        if(j%2)

        {
            //QString s=QString(QString::fromLocal8Bit(it->second->name.c_str()));
            QTableWidgetItem *item = new QTableWidgetItem
                    (QString::fromLocal8Bit(it->second.name.c_str()));
            //item->setBackground(QBrush(QColor(255,255,255)));
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            ui->table_cost->setItem(j, 0, item);
            //ui->table_cost_2->setItem(j, 0, item);

            QTableWidgetItem *item3 = new QTableWidgetItem
                    (QString::number(it->second.times));
            //item2->setBackground(QBrush(QColor(255,255,255)));
            item3->setFlags(item3->flags() & (~Qt::ItemIsEditable));
            ui->table_cost->setItem(j, 1, item3);
            //ui->table_cost_2->setItem(j, 1, item3);

            //QString s1=QString(QString::fromLocal8Bit(it->second->timelong.c_str()));
            QTableWidgetItem *item1 = new QTableWidgetItem
                    (QString::fromLocal8Bit(it->second.timelong.c_str()));
            //item1->setBackground(QBrush(QColor(255,255,255)));
            item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
            ui->table_cost->setItem(j, 2, item1);
            //ui->table_cost_2->setItem(j, 2, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem
                    (QString::number(it->second.cost));
            //item2->setBackground(QBrush(QColor(255,255,255)));
            item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
            ui->table_cost->setItem(j, 3, item2);
            //ui->table_cost_2->setItem(j, 3, item2);
        }
        else
        {
            QTableWidgetItem *item = new QTableWidgetItem
                    (QString::fromLocal8Bit(it->second.name.c_str()));
            item->setBackground(QBrush(QColor(106,106,106)));
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            ui->table_cost->setItem(j, 0, item);
            //ui->table_cost_2->setItem(j, 0, item);

            QTableWidgetItem *item3 = new QTableWidgetItem
                    (QString::number(it->second.times));
            item3->setBackground(QBrush(QColor(106,106,106)));
            item3->setFlags(item3->flags() & (~Qt::ItemIsEditable));
            ui->table_cost->setItem(j, 1, item3);
            //ui->table_cost_2->setItem(j, 1, item3);

            //QString s1=QString(QString::fromLocal8Bit(it->second->timelong.c_str()));
            QTableWidgetItem *item1 = new QTableWidgetItem
                    (QString::fromLocal8Bit(it->second.timelong.c_str()));
            item1->setBackground(QBrush(QColor(106,106,106)));
            item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
            ui->table_cost->setItem(j, 2, item1);
            //ui->table_cost_2->setItem(j, 2, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem
                    (QString::number(it->second.cost));
            item2->setBackground(QBrush(QColor(106,106,106)));
            item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
            ui->table_cost->setItem(j, 3, item2);
            //ui->table_cost_2->setItem(j, 3, item2);
        }

    }
    //show log on table_cost2
    j=0;
    for( map<string,table> ::iterator it=mt.begin();it!=mt.end();++it,++j)
    {
        if(j%2)

        {
            //QString s=QString(QString::fromLocal8Bit(it->second->name.c_str()));
            QTableWidgetItem *item = new QTableWidgetItem
                    (QString::fromLocal8Bit(it->second.name.c_str()));
            //item->setBackground(QBrush(QColor(255,255,255)));
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            //ui->table_cost->setItem(j, 0, item);
            ui->table_cost_2->setItem(j, 0, item);

            QTableWidgetItem *item3 = new QTableWidgetItem
                    (QString::number(it->second.times));
            //item2->setBackground(QBrush(QColor(255,255,255)));
            item3->setFlags(item3->flags() & (~Qt::ItemIsEditable));
            //ui->table_cost->setItem(j, 1, item3);
            ui->table_cost_2->setItem(j, 1, item3);

            //QString s1=QString(QString::fromLocal8Bit(it->second->timelong.c_str()));
            QTableWidgetItem *item1 = new QTableWidgetItem
                    (QString::fromLocal8Bit(it->second.timelong.c_str()));
            //item1->setBackground(QBrush(QColor(255,255,255)));
            item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
            //ui->table_cost->setItem(j, 2, item1);
            ui->table_cost_2->setItem(j, 2, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem
                    (QString::number(it->second.cost));
            //item2->setBackground(QBrush(QColor(255,255,255)));
            item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
            //ui->table_cost->setItem(j, 3, item2);
            ui->table_cost_2->setItem(j, 3, item2);
        }
        else
        {
            QTableWidgetItem *item = new QTableWidgetItem
                    (QString::fromLocal8Bit(it->second.name.c_str()));
            item->setBackground(QBrush(QColor(106,106,106)));
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            //ui->table_cost->setItem(j, 0, item);
            ui->table_cost_2->setItem(j, 0, item);

            QTableWidgetItem *item3 = new QTableWidgetItem
                    (QString::number(it->second.times));
            item3->setBackground(QBrush(QColor(106,106,106)));
            item3->setFlags(item3->flags() & (~Qt::ItemIsEditable));
            //ui->table_cost->setItem(j, 1, item3);
            ui->table_cost_2->setItem(j, 1, item3);

            //QString s1=QString(QString::fromLocal8Bit(it->second->timelong.c_str()));
            QTableWidgetItem *item1 = new QTableWidgetItem
                    (QString::fromLocal8Bit(it->second.timelong.c_str()));
            item1->setBackground(QBrush(QColor(106,106,106)));
            item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
            //ui->table_cost->setItem(j, 2, item1);
            ui->table_cost_2->setItem(j, 2, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem
                    (QString::number(it->second.cost));
            item2->setBackground(QBrush(QColor(106,106,106)));
            item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
            //ui->table_cost->setItem(j, 3, item2);
            ui->table_cost_2->setItem(j, 3, item2);
        }

    }

}
void MainWindow::searchrec()
{
    clearrec2();
    ui->table_cost_2->setColumnCount(4);
    ui->table_cost_2->setRowCount(mt.size());



    ui->table_cost_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->table_cost_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_cost_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->table_cost_2->verticalHeader()->setVisible(true);
    ui->table_cost_2->setShowGrid(true);
    //ui->table_cost_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条

    ui->table_cost_2->setColumnWidth(0,110);
    ui->table_cost_2->setColumnWidth(1,110);
    ui->table_cost_2->setColumnWidth(2,110);
    ui->table_cost_2->setColumnWidth(3,110);
    QStringList header;
    header<<"User Name"<<"Login Times"<<"Log Timelong"<<"Charge(Yuan)";
    ui->table_cost_2->setHorizontalHeaderLabels(header);

    int j=0;
    for( map<string,table> ::iterator it=mt.begin();it!=mt.end();++it)
    {

        if(searchCondition(it))
            if(j%2)
            {
                //QString s=QString(QString::fromLocal8Bit(it->second->name.c_str()));
                QTableWidgetItem *item = new QTableWidgetItem
                        (QString::fromLocal8Bit(it->second.name.c_str()));
                //item->setBackground(QBrush(QColor(255,255,255)));
                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
                ui->table_cost_2->setItem(j, 0, item);

                QTableWidgetItem *item3 = new QTableWidgetItem
                        (QString::number(it->second.times));
                //item2->setBackground(QBrush(QColor(255,255,255)));
                item3->setFlags(item3->flags() & (~Qt::ItemIsEditable));
                ui->table_cost_2->setItem(j, 1, item3);

                //QString s1=QString(QString::fromLocal8Bit(it->second->timelong.c_str()));
                QTableWidgetItem *item1 = new QTableWidgetItem
                        (QString::fromLocal8Bit(it->second.timelong.c_str()));
                //item1->setBackground(QBrush(QColor(255,255,255)));
                item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
                ui->table_cost_2->setItem(j, 2, item1);

                QTableWidgetItem *item2 = new QTableWidgetItem
                        (QString::number(it->second.cost));
                //item2->setBackground(QBrush(QColor(255,255,255)));
                item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
                ui->table_cost_2->setItem(j, 3, item2);
                ++j;
            }
            else
            {
                QTableWidgetItem *item = new QTableWidgetItem
                        (QString::fromLocal8Bit(it->second.name.c_str()));
                item->setBackground(QBrush(QColor(106,106,106)));
                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
                ui->table_cost_2->setItem(j, 0, item);

                QTableWidgetItem *item3 = new QTableWidgetItem
                        (QString::number(it->second.times));
                item3->setBackground(QBrush(QColor(106,106,106)));
                item3->setFlags(item3->flags() & (~Qt::ItemIsEditable));
                ui->table_cost_2->setItem(j, 1, item3);

                //QString s1=QString(QString::fromLocal8Bit(it->second->timelong.c_str()));
                QTableWidgetItem *item1 = new QTableWidgetItem
                        (QString::fromLocal8Bit(it->second.timelong.c_str()));
                item1->setBackground(QBrush(QColor(106,106,106)));
                item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
                ui->table_cost_2->setItem(j, 2, item1);

                QTableWidgetItem *item2 = new QTableWidgetItem
                        (QString::number(it->second.cost));
                item2->setBackground(QBrush(QColor(106,106,106)));
                item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
                ui->table_cost_2->setItem(j, 3, item2);
                ++j;
            }

    }
}

bool MainWindow::searchCondition(map<string,table> ::iterator &it)
{
    bool conditionName = true;
    bool conditionTimes = true;
    bool conditionCharge = true;
    QString searchName = ui->lineEdit_name->text();
    float itTimes(it->second.times);
    float itCharge(it->second.cost);
    float conTimes = ui->lineEdit_conTimes->text().toFloat();
    float conCharge = ui->lineEdit_conCharge->text().toFloat();
    if(!searchName.isEmpty())
        conditionName =  QString::fromLocal8Bit(it->second.name.c_str()).contains(searchName,Qt::CaseSensitive);


    if(!ui->lineEdit_conTimes->text().isEmpty())
        switch(ui->comboBox_times->currentIndex())
        {

        case 0:
            conditionTimes = (qAbs(conTimes - itTimes) <= 1e-6) ;
            break;
        case 1:
            conditionTimes = (itTimes < conTimes) ;
            break;
        case 2:
            conditionTimes = (itTimes <= conTimes) ;
            break;
        case 3:
            conditionTimes = (itTimes > conTimes) ;
            break;
        case 4:
            conditionTimes = (itTimes >= conTimes) ;
            break;
        case 5:
            conditionTimes = (qAbs(conTimes - itTimes) > 1e-6) ;
            break;
        }
    if(!ui->lineEdit_conCharge->text().isEmpty())
        switch(ui->comboBox_charge->currentIndex())
        {

        case 0:
            conditionCharge = (qAbs(conCharge - itCharge) <= 1e-6) ;
            break;
        case 1:
            conditionCharge = (itCharge < conCharge) ;
            break;
        case 2:
            conditionCharge = (itCharge <= conCharge) ;
            break;
        case 3:
            conditionCharge = (itCharge > conCharge) ;
            break;
        case 4:
            conditionCharge = (itCharge >= conCharge) ;
            break;
        case 5:
            conditionCharge = (qAbs(conCharge - itCharge) > 1e-6) ;
            break;
        }
    return conditionName && conditionTimes && conditionCharge;
}

void MainWindow::clearrec()
{
    for(int i = ui->table_cost->rowCount()-1;i>=0 ;--i)
    {
        ui->table_cost->removeRow(i);
    }

}

void MainWindow::clearrec2()
{
    for(int i = ui->table_cost_2->rowCount()-1;i>=0 ;--i)
    {
        ui->table_cost_2->removeRow(i);
    }
}

void MainWindow::skinChange()
{
    styleSheetEditor->show();
    styleSheetEditor->activateWindow();
}

void MainWindow::aboutInfo()
{
    QMessageBox::about(this, tr("About the server of DMS system"),
                       tr("The <b>DMS System Server</b> give the function of getting the reports of<br />"
                          "year or month or day.<br />"
                          "The source codes are shared on <a href=\"https://coding.net/u/NickelCAo/p/DMS-4.0/git\">NickelCAo/DMS-4.0</a> on Coding.net.<br />"
                          "Created by No.5 Programing Group."
                          ));
}

void MainWindow::quitProgram()
{
    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
