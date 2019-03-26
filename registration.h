#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QString>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QThread>
#include "authorization.h"
#include <QVariantMap>

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0);
    ~Registration();
    void signupFunction();

private slots:
    void onTextChanged();

    void on_register_button_clicked();

    void on_firstname_text_editingFinished();

    void on_lastname_text_editingFinished();

    void on_username_text_editingFinished();

    void on_password_text_editingFinished();

    void on_username_text_textChanged();

    void on_password_text_textChanged();

    void signupNetworkReply(QNetworkReply *reply);

    void on_firstname_text_textChanged();

    void on_lastname_text_textChanged();

    void ConnectionCheckFunc();

    void on_pushButton_clicked();

private:
    Ui::Registration *ui;
    QTimer *timer;
    int firstname_t;
    int lastname_t;
    QString firstname;
    QString lastname;
    QString username;
    QString password;
    QNetworkAccessManager *manager;

};

#endif // REGISTRATION_H
