#include "logout.h"
#include "ui_logout.h"

logout::logout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logout)
{
    ui->setupUi(this);
}

logout::~logout()
{
    delete ui;
}
