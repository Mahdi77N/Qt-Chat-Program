#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QWidget>
#include "generalpage.h"
#include "QString"

namespace Ui {
class addContact;
}

class addContact : public QWidget
{
    Q_OBJECT

public:
    explicit addContact(QWidget *parent = 0);
    ~addContact();

private slots:
    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged();

    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

    void addContactSlot(QNetworkReply *reply);

private:
    Ui::addContact *ui;
    QString username;
};

#endif // ADDCONTACT_H
