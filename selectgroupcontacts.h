#ifndef SELECTGROUPCONTACTS_H
#define SELECTGROUPCONTACTS_H

#include <QWidget>

namespace Ui {
class SelectGroupContacts;
}

class SelectGroupContacts : public QWidget
{
    Q_OBJECT

public:
    explicit SelectGroupContacts(QWidget *parent = 0);
    ~SelectGroupContacts();

private:
    Ui::SelectGroupContacts *ui;
};

#endif // SELECTGROUPCONTACTS_H
