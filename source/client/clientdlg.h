#ifndef CLIENTDLG_H
#define CLIENTDLG_H

#include <QMainWindow>
#include "workthread.h"
#include "data.h"
#include <time.h>
#include "stylesheeteditor.h"
namespace Ui {
class clientdlg;
}

class clientdlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientdlg(QWidget *parent = 0);
    ~clientdlg();
    std::string getStringFromLong(long long_time);
    QString stoq(const string &s);
    string qtos(const QString &s);
    string gettimelong(long long_time);
    string ipAddress;
public slots:
    void startsend();
    void updatetable(MLogRec log);
    void cleartable();
    void logout();
    void editStyleAction_triggered();
    void aboutAction_triggered();
    //void timesend();
private:
    QAction *startAction;
    QAction *clearAction;
    QAction *logoutAction;
    QAction *editStyleAction;
    QAction *aboutAction;
    WorkThread* m_work;
    int count;
    StyleSheetEditor *styleSheetEditor;
    Ui::clientdlg *ui;
private slots:

};

#endif // CLIENTDLG_H
