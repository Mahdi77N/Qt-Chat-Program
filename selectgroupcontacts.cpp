#include "selectgroupcontacts.h"
#include "ui_selectgroupcontacts.h"

SelectGroupContacts::SelectGroupContacts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectGroupContacts)
{
    ui->setupUi(this);
}

SelectGroupContacts::~SelectGroupContacts()
{
    delete ui;
}
