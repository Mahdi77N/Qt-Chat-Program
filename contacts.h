#ifndef CONTACTS_H
#define CONTACTS_H

#include <QWidget>
#include "connectioncheck.h"
#include <QThread>
#include <QTimer>
#include "client.h"
#include "QNetworkAccessManager"
#include "jsonconverter.h"
#include <QVariantMap>
#include "generalpage.h"
#include <QMessageBox>
#include "getfromfile.h"
#include "getfromserver.h"
#include "messageing.h"


namespace Ui {
class Contacts;
}

class Contacts : public QWidget
{
    Q_OBJECT

public:
    explicit Contacts(QWidget *parent = 0);
    ~Contacts();
    bool checkExistance(QString s);

private slots:
    void ConnectionCheckFunc();

    void on_back_button_clicked();

    void on_search_button_clicked();

    void on_contact_name_textChanged();

    void on_contact_name_editingFinished();

    void on_pushButton_clicked();

public slots:
        void gettingFromServer();

private:
    Ui::Contacts *ui;
    QString contact;
    QTimer *timer_t;
    QTimer *timer;
    //Client *client_t;
    int userSize;
    QString *Lists;
};

#endif // CONTACTS_H
