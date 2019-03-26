#ifndef GENERALPAGE_H
#define GENERALPAGE_H

#include <QWidget>
#include "connectioncheck.h"
#include <QThread>
#include <QTimer>
#include "client.h"
#include <QString>
#include "jsonconverter.h"
#include <QMessageBox>
#include "authorization.h"
#include "creategroupe.h"
#include "createchannal.h"
#include "joinchannal.h"
#include "joingroup.h"
#include "groups.h"
#include "channals.h"
#include "contacts.h"
#include "fileworking.h"
#include "getfromserver.h"
#include "getfromfile.h"
#include "messageing.h"


namespace Ui {
class GeneralPage;
}

class GeneralPage : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralPage(QWidget *parent = 0);
    ~GeneralPage();

private slots:
    void on_contacts_button_clicked();

    void on_addContact_button_clicked();

    void on_groups_button_clicked();

    void on_joinGroup_button_clicked();

    void on_channals_button_clicked();

    void on_joinChannal_button_clicked();

    void on_createGroup_button_clicked();

    void on_createChannal_button_clicked();

    void on_logout_button_clicked();
    void logoutReply(QNetworkReply *reply);

    void ConnectionCheckFunc();

    void serverConnectionGetFile();

private:
    Ui::GeneralPage *ui;
    QTimer *timer;
    QTimer *server_connection_timer;
    Client *client_t;
    QNetworkAccessManager *manager;

};

#endif // GENERALPAGE_H
