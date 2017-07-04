#ifndef UREGISTER_H
#define UREGISTER_H

#include <QDialog>
#include <string>
namespace Ui {
class uregister;
}

class uregister : public QDialog
{
    Q_OBJECT
public slots:
    void usubmit();
    void ureset();
public:
    explicit uregister(QWidget *parent = 0);
    ~uregister();
    std::string ipAddress;

private:
    Ui::uregister *ui;
};

#endif // UREGISTER_H
