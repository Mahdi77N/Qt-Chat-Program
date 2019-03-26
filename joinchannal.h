#ifndef JOINCHANNAL_H
#define JOINCHANNAL_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QString>
#include <QMessageBox>
#include "generalpage.h"
#include <QTimer>
#include <QThread>
#include "client.h"
#include "connectioncheck.h"
#include "jsonconverter.h"


namespace Ui {
class joinChannal;
}

class joinChannal : public QWidget
{
    Q_OBJECT

public:
    explicit joinChannal(QWidget *parent = 0);
    ~joinChannal();
    void joinchannalFunction();

private slots:
    void joinchannalReply(QNetworkReply *reply);

    void ConnectionCheckFunc();

    void on_join_button_clicked();

    void on_back_button_clicked();

    void on_channal_name_textChanged();

    void on_channal_name_editingFinished();

private:
    Ui::joinChannal *ui;
    QString token;
    QString name;
    QTimer *timer;
    Client *client_t;
    QNetworkAccessManager *manager;

};

#endif // JOINCHANNAL_H
