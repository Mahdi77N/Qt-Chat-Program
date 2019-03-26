#ifndef JOINGROUP_H
#define JOINGROUP_H

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
class joinGroup;
}

class joinGroup : public QWidget
{
    Q_OBJECT

public:
    explicit joinGroup(QWidget *parent = 0);
    ~joinGroup();
    void joingroupFunction();

private slots:
    void joingroupReply(QNetworkReply *reply);

    void ConnectionCheckFunc();

    void on_join_button_clicked();

    void on_group_name_textChanged();

    void on_group_name_editingFinished();

private:
    Ui::joinGroup *ui;
    QString token;
    QString name;
    QTimer *timer;
    Client *client_t;
    QNetworkAccessManager *manager;
};

#endif // JOINGROUP_H
