#include "getfromserver.h"

getFromServer::getFromServer(QObject *parent) : QObject(parent)
{
    client_t = new Client;
    client_t->readTokenFile();
    token = client_t->getToken();
    userListManager = new QNetworkAccessManager;
    groupListManager = new QNetworkAccessManager;
    channelListManager = new QNetworkAccessManager;
}

getFromServer::~getFromServer(){
    delete client_t;
    //delete manager;
    //delete manager_t;
    delete userListManager;
    delete groupListManager;
    delete channelListManager;
    for(int i = 0; i < userSize; i++)
        delete userChatManager[i];
    for(int i = 0; i < groupSize; i++)
        delete groupChatManager[i];
    for(int i = 0; i < channelSize; i++)
        delete channelChatManager[i];
}

void getFromServer::runGetting(){
    getUsersList();
    getChannelsList();
    getGroupsList();
}

//Get user list
void getFromServer::getUsersList(){
    connect(userListManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getUsersListSlot(QNetworkReply*)));
    QString request = "http://api.softserver.org:1104/getuserlist?token=" + token;
    userListManager->get(QNetworkRequest(QUrl(request)));
}
void getFromServer::getUsersListSlot(QNetworkReply *reply){
    fileWorking *file = new fileWorking;
    file->fileSet(reply);
    file->runConverting();
    file->setUsersList();
    userSize = file->getBlockNumbers();
    userChatManager = new QNetworkAccessManager*[userSize];
    for(int i = 0; i < userSize; i++)
        userChatManager[i] = new QNetworkAccessManager;
    getUsersChats();
    delete file;
}

//Get group list
void getFromServer::getGroupsList(){
    connect(groupListManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getGroupsListSlot(QNetworkReply*)));
    QString request = "http://api.softserver.org:1104/getgrouplist?token=" + token;
    groupListManager->get(QNetworkRequest(QUrl(request)));
}
void getFromServer::getGroupsListSlot(QNetworkReply *reply){
    fileWorking *file = new fileWorking;
    file->fileSet(reply);
    file->runConverting();
    file->setGroupsList();
    groupSize = file->getBlockNumbers();
    groupChatManager = new QNetworkAccessManager*[groupSize];
    for(int i = 0; i < groupSize; i++)
        groupChatManager[i] = new QNetworkAccessManager;
    getGroupsChats();
    delete file;
}

//Get channel list
void getFromServer::getChannelsList(){
    connect(channelListManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getChannelsListSlot(QNetworkReply*)));
    QString request = "http://api.softserver.org:1104/getchannellist?token=" + token;;
    channelListManager->get(QNetworkRequest(QUrl(request)));
}
void getFromServer::getChannelsListSlot(QNetworkReply *reply){
    fileWorking *file = new fileWorking;
    file->fileSet(reply);
    file->runConverting();
    file->setChannelsList();
    channelSize = file->getBlockNumbers();
    channelChatManager = new QNetworkAccessManager*
            [channelSize];
    for(int i = 0; i < channelSize; i++)
        channelChatManager[i] = new QNetworkAccessManager;
    getChannelsChats();
    delete file;


}

//Get user chats
void getFromServer::getUsersChats(){
    QFile file("E:/Programming/AP Project/Texts/UsersList.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingServer)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    users = new QString[userSize];
    for(int i = 0; i < userSize; i++){
        users[i] = in.readLine();
    }
    file.close();
    QString request;
    for(int i = 0; i < userSize; i++){
        request = "http://api.softserver.org:1104/getuserchats?token=" + token + "&dst=" + users[i];
        connect(userChatManager[i], SIGNAL(finished(QNetworkReply*)), this, SLOT(getUsersChatsSlot(QNetworkReply*)));
        userChatManager[i]->get(QNetworkRequest(QUrl(request)));
    }
}
void getFromServer::getUsersChatsSlot(QNetworkReply *reply){
    fileWorking *file = new fileWorking;
    file->fileSet(reply);
    file->runConverting();
    //QMessageBox msg;
    //msg.setText(users[j]);
    //msg.exec();
    file->setUserChats();
    delete file;
}


//Get channel chats
void getFromServer::getChannelsChats(){
    QFile file("E:/Programming/AP Project/Texts/ChannelsList.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingServer)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    QString channels[channelSize];
    for(int i = 0; i < channelSize; i++){
        channels[i] = in.readLine();
    }
    file.close();
    QString request;
    for(int i = 0; i < channelSize; i++){
        request = "http://api.softserver.org:1104/getchannelchats?token=" + token + "&dst=" + channels[i];
        connect(channelChatManager[i], SIGNAL(finished(QNetworkReply*)), this, SLOT(getChannelsChatsSlot(QNetworkReply*)));
        channelChatManager[i]->get(QNetworkRequest(QUrl(request)));
    }
}
void getFromServer::getChannelsChatsSlot(QNetworkReply *reply){
    fileWorking *file = new fileWorking;
    file->fileSet(reply);
    file->runConverting();
    file->setChannelChats();
    delete file;
}


//Get group chats
void getFromServer::getGroupsChats(){
    QFile file("E:/Programming/AP Project/Texts/GroupsList.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingServer)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    QString groups[groupSize];
    for(int i = 0; i < groupSize; i++){
        groups[i] = in.readLine();
    }
    file.close();
    QString request;
    for(int i = 0; i < groupSize; i++){
        request = "http://api.softserver.org:1104/getgroupchats?token=" + token + "&dst=" + groups[i];
        connect(groupChatManager[i], SIGNAL(finished(QNetworkReply*)), this, SLOT(getGroupsChatsSlot(QNetworkReply*)));
        groupChatManager[i]->get(QNetworkRequest(QUrl(request)));
    }
}
void getFromServer::getGroupsChatsSlot(QNetworkReply *reply){
    fileWorking *file = new fileWorking;
    file->fileSet(reply);
    file->runConverting();
    file->setGroupChats();
    delete file;
}
