#ifndef CREATECHANNAL_H
#define CREATECHANNAL_H

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
class CreateChannal;
}

class CreateChannal : public QWidget
{
    Q_OBJECT

public:
    explicit CreateChannal(QWidget *parent = 0);
    ~CreateChannal();
    void createchannalFunction();

    
private slots:
    void ConnectionCheckFunc();
    
    void createchannalReply(QNetworkReply *reply);
    
    void on_channal_name_textChanged();
    
    void on_cancel_button_clicked();

    void on_create_channal_clicked();

    void on_channal_title_editingFinished();

    void on_channal_name_editingFinished();

    void on_channal_title_textChanged();

private:
    Ui::CreateChannal *ui;
    QTimer *timer;
    Client *client_t;
    QString token;
    QString title;
    int title_t;
    QString name;
    QNetworkAccessManager *manager;
    
    
    
};

#endif // CREATECHANNAL_H
