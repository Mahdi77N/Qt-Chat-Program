#ifndef MESSAGEING_H
#define MESSAGEING_H

#include <QWidget>
#include <QDialog>
#include <QObject>
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
#include "contacts.h"
#include "channals.h"
#include "groups.h"

namespace Ui {
class Messageing;
}

class Messageing : public QWidget
{
    Q_OBJECT

public:
    explicit Messageing(QString chatType_t, QString chatName_t, QWidget *parent = 0);
    ~Messageing();

private slots:
    void gettingFromServer();

    void ConnectionCheckFunc();

    void on_back_button_clicked();

    void on_message_lineedit_textChanged();

    void on_message_lineedit_editingFinished();

    void on_Send_Button_clicked();

    void sendMessage(QNetworkReply *reply);

    void on_pushButton_clicked();

private:
    Ui::Messageing *ui;
    QString chatType;
    QString chatName;
    QTimer *timer;
    QTimer *timer_t;
    Client *client_t;
    QString **Lists;
    int chatSize;
    QString token;
    QString messageText;
};

#endif // MESSAGEING_H
