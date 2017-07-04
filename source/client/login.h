#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
using namespace  std;

namespace Ui {
class loginwindow;
}

class loginwindow : public QDialog
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = 0);
    ~loginwindow();
    string qtos( QString s);
    string ipAddress;
    //string loginwindow::qtos(QString &s)
public slots:
    void islogin();
    void lregister();
private slots:
    void on_myExit_clicked();

private:
    Ui::loginwindow *ui;
};

#endif // LOGIN_H
