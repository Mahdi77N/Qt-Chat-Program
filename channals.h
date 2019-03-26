#ifndef CHANNALS_H
#define CHANNALS_H

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
class Channals;
}

class Channals : public QWidget
{
    Q_OBJECT

public:
    explicit Channals(QWidget *parent = 0);
    ~Channals();
    bool checkExistance(QString s);

private slots:


    void ConnectionCheckFunc();

    void on_back_button_clicked();

    void on_search_button_clicked();

    void on_channal_name_textChanged();

    void on_channal_name_editingFinished();

    void on_pushButton_clicked();

public slots:
    void gettingFromServer();

private:
    Ui::Channals *ui;
    QString contact;
    QTimer *timer_t;
    QTimer *timer;
    int channelSize;
    QString *Lists;
};

#endif // CHANNALS_H
