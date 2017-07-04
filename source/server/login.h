#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    QString uid;
    QString upassword;
    explicit login(QWidget *parent = 0);
    ~login();
public slots:
    void check();
    void reset();
private:
    Ui::login *ui;
};

#endif // LOGIN_H
