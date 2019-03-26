#ifndef CREATEGROUPE_H
#define CREATEGROUPE_H

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
class CreateGroupe;
}

class CreateGroupe : public QWidget
{
    Q_OBJECT

public:
    explicit CreateGroupe(QWidget *parent = 0);
    ~CreateGroupe();
    void creategroupFunction();

private slots:
    void ConnectionCheckFunc();

    void creategroupReply(QNetworkReply *reply);

    void on_group_name_editingFinished();

    void on_c_clicked();

    void on_group_title_editingFinished();

    void on_group_name_textChanged();

    void on_group_title_textChanged();

    void on_create_group_clicked();

private:
    Ui::CreateGroupe *ui;
    QTimer *timer;
    Client *client_t;
    QString token;
    QString title;
    int title_t;
    QString name;
    QNetworkAccessManager *manager;
};

#endif // CREATEGROUPE_H
