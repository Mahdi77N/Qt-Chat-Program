#ifndef CONNECTIONCHECK_H
#define CONNECTIONCHECK_H

#include <QObject>
#include <QtNetwork>


class ConnectionCheck
{
private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop loop;
public:
    int connectOrNot();
};

#endif // CONNECTIONCHECK_H
