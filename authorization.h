#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include "registration.h"
#include "connectioncheck.h"
#include <QThread>
#include <QTimer>
#include "client.h"
#include "QNetworkAccessManager"
#include "jsonconverter.h"
#include <QVariantMap>
#include "generalpage.h"
#include <QMessageBox>

namespace Ui {
class authorization;
}

class authorization : public QWidget
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = 0);
    ~authorization();
    void signinFunction();


private slots:
    void onTextChanged();

    void on_signUp_button_clicked();

    void on_signIn_button_clicked();

    void on_username_text_textChanged();

    void on_password_text_textChanged();

    void ConnectionCheckFunc();

    void signinNetworkReply(QNetworkReply *reply);

    void on_username_text_editingFinished();

    void on_password_text_editingFinished();

private:
    Ui::authorization *ui;
    QTimer *timer;
    Client *client_t;
    QString username;
    QString password;
    QNetworkAccessManager *manager;
};

#endif // AUTHORIZATION_H
