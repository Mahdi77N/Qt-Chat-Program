#include "getfromfile.h"
getFromFile::getFromFile(){
    userSize = 0;
    channelSize = 0;
    groupSize = 0;
    fileUserList();
    fileChannelList();
    fileGroupList();
}

QString *getFromFile::getUserList(){return UserList;}
QString *getFromFile::getGroupList(){return GroupList;}
QString *getFromFile::getChannelList(){return ChannelList;}


QString **getFromFile::getUserChats(QString userName){
    fileUserChats(userName);
    return UserChats;
}
QString **getFromFile::getGroupChats(QString groupName){
    fileGroupChats(groupName);
    return GroupChats;
}
QString **getFromFile::getChannelChats(QString channelName){
    fileChannelChats(channelName);
    return ChannelChats;
}
int getFromFile::getUserSize(){return userSize;}
int getFromFile::getChannelSize(){return channelSize;}
int getFromFile::getGroupSize(){return groupSize;}




void getFromFile::fileUserList(){
    QFile file("E:/Programming/AP Project/Texts/UsersList.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    while( !in.atEnd()){
        in.readLine();
        userSize++;
    }
    in.seek(0);
    UserList = new QString[userSize];
    for(int i = 0; i < userSize; i++)
        UserList[i] = in.readLine();
    file.close();
    UserChats[0] = new QString[userSize];
    UserChats[1] = new QString[userSize];

}




void getFromFile::fileGroupList(){
    QFile file("E:/Programming/AP Project/Texts/GroupsList.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    while( !in.atEnd()){
        in.readLine();
        groupSize++;
    }
    in.seek(0);
    GroupList = new QString[groupSize];
    for(int i = 0; i < groupSize; i++)
        GroupList[i] = in.readLine();
    file.close();
    GroupChats[0] = new QString[groupSize];
    GroupChats[1] = new QString[groupSize];
}




void getFromFile::fileChannelList(){
    QFile file("E:/Programming/AP Project/Texts/ChannelsList.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    while( !in.atEnd()){
        in.readLine();
        channelSize++;
    }
    in.seek(0);
    ChannelList = new QString[channelSize];
    for(int i = 0; i < channelSize; i++)
        ChannelList[i] = in.readLine();
    file.close();
    ChannelChats[0] = new QString[channelSize];
    ChannelChats[1] = new QString[channelSize];
}




void getFromFile::fileUserChats(QString userName){
    //fileUserList();
    QFile file("E:/Programming/AP Project/Texts/Users/" + userName + "_src.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    for(int i = 0; i < userSize; i++)
        UserChats[0][i] = in.readLine();
    file.close();

    QFile file2("E:/Programming/AP Project/Texts/Users/" + userName + "_body.txt");
    if(!file2.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in2(&file2);
    for(int i = 0; i < userSize; i++)
        UserChats[1][i] = in2.readLine();
    file2.close();
}





void getFromFile::fileGroupChats(QString groupName){
    //fileGroupList();
    QFile file("E:/Programming/AP Project/Texts/Groups/" + groupName + "_src.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    for(int i = 0; i < groupSize; i++)
        GroupChats[0][i] = in.readLine();
    file.close();

    QFile file2("E:/Programming/AP Project/Texts/Groups/" + groupName + "_body.txt");
    if(!file2.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in2(&file2);
    for(int i = 0; i < groupSize; i++)
        GroupChats[1][i] = in2.readLine();
    file2.close();
}





void getFromFile::fileChannelChats(QString channelName){
    //fileChannelList();
    QFile file("E:/Programming/AP Project/Texts/Channels/" + channelName + "_src.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in(&file);
    for(int i = 0; i < userSize; i++)
        ChannelChats[0][i] = in.readLine();
    file.close();

    QFile file2("E:/Programming/AP Project/Texts/Channels/" + channelName + "_body.txt");
    if(!file2.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (gettingFromFile)");
        msg.exec();
        exit(0);
    }
    QTextStream in2(&file2);
    for(int i = 0; i < channelSize; i++)
        ChannelChats[1][i] = in2.readLine();
    file2.close();
}
