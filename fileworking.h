#ifndef FILEWORKING_H
#define FILEWORKING_H

#include <QFile>
#include <QString>
#include "jsonconverter.h"
#include <QVariantMap>
#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QChar>


class fileWorking : public QObject
{
public:
    //fileWorking();
    //~fileWorking();
    void fileSet(QNetworkReply *reply_t);
    void writeFile(QString address_f, QString Text[], int lineNumbers);
    void runConverting();
    int getBlockNumbers();
    //void setChats(QString typeChat);
    void setUserChats();
    void setChannelChats();
    void setGroupChats();
    void setList(QString typeList, QString sourceName);
    void setUsersList();
    void setGroupsList();
    void setChannelsList();


private:
    QNetworkReply *reply;
    int blockNumbers;
    QVariantMap json_map;
};

#endif // FILEWORKING_H
