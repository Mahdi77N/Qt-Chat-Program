#include "fileworking.h"
#include "client.h"

void fileWorking::fileSet(QNetworkReply *reply_t){
    reply = reply_t;
}

int fileWorking::getBlockNumbers(){
    return blockNumbers;
}

void fileWorking::runConverting(){
    //Read Json reply and convert it to QVarientmap
    JsonConverter *json = new JsonConverter;
    json->setJsonByte(reply->readAll());
    json->runJsonConverter();
    json_map = json->getJsonMap();
    delete json;

    //Set Block Numbers
    QString message = json_map["message"].toString();
    QString blockSize;
    for(int i = 0; i < message.size(); i++){
        if(message[i] == '-'){
            for(int j = i + 1, k = 0; 1; j++, k++){
                if(message[j] == '-')
                    break;
                blockSize[k] = message[j];
            }
            break;
        }
    }
    blockNumbers = blockSize.toInt();

}


//set channal chats
void fileWorking::setChannelChats(){
    QString blockS;
    QString src[blockNumbers];
    QString body[blockNumbers];
    QString name;
    QVariantMap s;
    if(blockNumbers != 0){
        s = json_map["block 0"].toMap();
        name = s["dst"].toString();
    }
    for(int i = 0; i < blockNumbers; i++){
        blockS = "block " + QString::number(i);
        s = json_map[blockS].toMap();
        src[i] = s["src"].toString();
        body[i] = s["body"].toString();
    }
    QString address_tt;
    address_tt = "E:/Programming/AP Project/Texts/Channels/" + name + "_src.txt";
    writeFile(address_tt, src, blockNumbers);
    address_tt = "E:/Programming/AP Project/Texts/Channels/" + name + "_body.txt";
    writeFile(address_tt, body, blockNumbers);
}
//set group Chats
void fileWorking::setGroupChats(){
    QString blockS;
    QString src[blockNumbers];
    QString body[blockNumbers];
    QString name;
    QVariantMap s;
    if(blockNumbers != 0){
        QVariantMap s = json_map["block 0"].toMap();
        name = s["dst"].toString();
    }
    for(int i = 0; i < blockNumbers; i++){
        blockS = "block " + QString::number(i);
        s = json_map[blockS].toMap();
        src[i] = s["src"].toString();
        body[i] = s["body"].toString();
    }
    QString address_tt;
    address_tt = "E:/Programming/AP Project/Texts/Groups/" + name + "_src.txt";
    writeFile(address_tt, src, blockNumbers);
    address_tt = "E:/Programming/AP Project/Texts/Groups/" + name + "_body.txt";
    writeFile(address_tt, body, blockNumbers);

}
//set user Chats
void fileWorking::setUserChats(){
    QString blockS;
    QString src[blockNumbers];
    QString body[blockNumbers];
    //QString name;

    QVariantMap s = json_map["block 0"].toMap();
    QString name = s["src"].toString();
    Client *c = new Client;
    c->readUsername();
    QString u = c->getUsername();
    if(u == name)
        name = s["dst"].toString();

    //QVariantMap s;

    for(int i = 0; i < blockNumbers; i++){
        blockS = "block " + QString::number(i);
        s = json_map[blockS].toMap();
        src[i] = s["src"].toString();
        body[i] = s["body"].toString();
    }

    QString address_tt;
    address_tt = "E:/Programming/AP Project/Texts/Users/" + name + "_src.txt";
    writeFile(address_tt, src, blockNumbers);
    address_tt = "E:/Programming/AP Project/Texts/Users/" + name + "_body.txt";
    writeFile(address_tt, body, blockNumbers);
}
/*//set chats Function
void fileWorking::setChats(QString typeChat){
    if(blockNumbers == 0)
        return;

    QString blockS;
    QString src[blockNumbers];
    QString body[blockNumbers];
    QString name;

    QVariantMap s = json_map["block 0"].toMap();
    name = s["dst"].toString();

    for(int i = 0; i < blockNumbers; i++){
        blockS = "block " + QString::number(i);
        s = json_map[blockS].toMap();
        src[i] = s["src"].toString();
        body[i] = s["body"].toString();
    }

    QString address_tt;
    address_tt = "E:/Programming/AP Project/Texts/" + typeChat + "/" + name + "_src.txt";
    writeFile(address_tt, src, blockNumbers);
    address_tt = "E:/Programming/AP Project/Texts/" + typeChat + "/" + name + "_body.txt";
    writeFile(address_tt, body, blockNumbers);


}*/

//set Users List
void fileWorking::setUsersList(){
    setList("UsersList", "src");
}
//set Groups List
void fileWorking::setGroupsList(){
    setList("GroupsList", "group_name");
}
//set Channels List
void fileWorking::setChannelsList(){
    setList("ChannelsList", "channel_name");
}
//set Lists Function
void fileWorking::setList(QString typeList, QString sourceName){
    QString blockS;
    QString names[blockNumbers];
    QVariantMap s;

    for(int i = 0; i < blockNumbers; i++){
        blockS = "block " + QString::number(i);
        s = json_map[blockS].toMap();
        names[i] = s[sourceName].toString();
    }

    QString address_tt;
    address_tt = "E:/Programming/AP Project/Texts/" + typeList + ".txt";
    writeFile(address_tt, names, blockNumbers);

}


//Write in Files
void fileWorking::writeFile(QString address_f, QString Text[], int lineNumbers){
    QFile file(address_f);
    if(!file.open(QIODevice::ReadWrite| QIODevice::Text)){
        QMessageBox msg;
        msg.setText("An error occured while openning file (fileWorking)");
        msg.exec();
        exit(0);
    }
    QTextStream stream(&file);
    for(int i = 0; i < lineNumbers; i++){
        stream << Text[i] << endl;
    }
    file.flush();
    file.close();
}
