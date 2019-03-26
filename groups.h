#ifndef GROUPS_H
#define GROUPS_H

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
class Groups;
}

class Groups : public QWidget
{
    Q_OBJECT

public:
    explicit Groups(QWidget *parent = 0);
    ~Groups();
    bool checkExistance(QString s);

private slots:
        void ConnectionCheckFunc();

        void on_back_button_clicked();

        void on_search_button_clicked();

        void on_group_name_textChanged();

        void on_group_name_editingFinished();

        void on_pushButton_clicked();

public slots:
        void gettingFromServer();

private:
    Ui::Groups *ui;
    QString contact;
    QTimer *timer_t;
    QTimer *timer;
    int groupSize;
    QString *Lists;
};

#endif // GROUPS_H
