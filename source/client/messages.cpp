#include "messages.h"
#include "ui_messages.h"

Messages::Messages(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Messages)
{
    ui->setupUi(this);
}

Messages::~Messages()
{
    delete ui;
}
