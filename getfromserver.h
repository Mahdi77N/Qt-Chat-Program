#ifndef GETFROMSERVER_H
#define GETFROMSERVER_H

#include "fileworking.h"
#include <QObject>
#include "client.h"
#include <QThread>

class getFromServer : public QObject
{
    Q_OBJECT
public:
    explicit getFromServer(QObject *parent = nullptr);
    ~getFromServer();
    void runGetting();
    void getUsersList();
    void getChannelsList();
    void getGroupsList();
    void getUsersChats();
    void getChannelsChats();
    void getGroupsChats();


private slots:
    void getUsersListSlot(QNetworkReply *reply);
    void getChannelsListSlot(QNetworkReply *reply);
    void getGroupsListSlot(QNetworkReply *reply);
    void getUsersChatsSlot(QNetworkReply *reply);
    void getChannelsChatsSlot(QNetworkReply *reply);
    void getGroupsChatsSlot(QNetworkReply *reply);

private:
    Client *client_t;
    QString token;
    int groupSize;
    int channelSize;
    int userSize;
    QString *users;
    QNetworkAccessManager *userListManager;
    QNetworkAccessManager *groupListManager;
    QNetworkAccessManager *channelListManager;
    QNetworkAccessManager **userChatManager;
    QNetworkAccessManager **groupChatManager;
    QNetworkAccessManager **channelChatManager;
};

#endif // GETFROMSERVER_H
