#ifndef MESSAGES_H
#define MESSAGES_H

#include <QMainWindow>

namespace Ui {
class Messages;
}

class Messages : public QMainWindow
{
    Q_OBJECT

public:
    explicit Messages(QWidget *parent = 0);
    ~Messages();

private:
    Ui::Messages *ui;
};

#endif // MESSAGES_H
