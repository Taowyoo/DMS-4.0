#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Conformity_Adress.h"
#include "stylesheeteditor.h"
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void printrec();
    void clearrec();
    void clearrec2();
    void skinChange();
    void aboutInfo();
    void quitProgram();
    void searchrec();
private:
    Ui::MainWindow *ui;
    Conformity_Adress conformity;
    StyleSheetEditor *styleSheetEditor;
    map<string,table> mt;
    bool searchCondition(map<string,table> ::iterator &it);
};

#endif // MAINWINDOW_H
