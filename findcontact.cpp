#include "findcontact.h"
#include "ui_findcontact.h"

FindContact::FindContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindContact)
{
    ui->setupUi(this);
}

FindContact::~FindContact()
{
    delete ui;
}
