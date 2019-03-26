#ifndef FINDCONTACT_H
#define FINDCONTACT_H

#include <QWidget>

namespace Ui {
class FindContact;
}

class FindContact : public QWidget
{
    Q_OBJECT

public:
    explicit FindContact(QWidget *parent = 0);
    ~FindContact();

private:
    Ui::FindContact *ui;
};

#endif // FINDCONTACT_H
