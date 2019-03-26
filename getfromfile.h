#ifndef GETFROMFILE_H
#define GETFROMFILE_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMessageBox>

class getFromFile
{
public:
    getFromFile();
    //~getFromFile();
    void fileUserList();
    void fileGroupList();
    void fileChannelList();
    void fileUserChats(QString userName);
    void fileGroupChats(QString groupName);
    void fileChannelChats(QString channelName);

    QString *getUserList();
    QString *getGroupList();
    QString *getChannelList();
    QString **getUserChats(QString userName);
    QString **getGroupChats(QString groupName);
    QString **getChannelChats(QString channelName);

    int getUserSize();
    int getChannelSize();
    int getGroupSize();

private:
    QString *UserChats[2];
    QString *ChannelChats[2];
    QString *GroupChats[2];
    QString *UserList;
    QString *GroupList;
    QString *ChannelList;

    int userSize;
    int channelSize;
    int groupSize;
};

#endif // GETFROMFILE_H
