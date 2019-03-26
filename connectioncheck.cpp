#include "connectioncheck.h"

int ConnectionCheck::connectOrNot(){
    reply = nullptr;
    manager = new QNetworkAccessManager();
    reply = manager->get(QNetworkRequest(QUrl("http://www.google.com")));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    delete manager;
    if(reply->error() == QNetworkReply::NoError)
        return 1;
    return 0;
}
