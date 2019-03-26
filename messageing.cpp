#include "messageing.h"
#include "ui_messageing.h"

Messageing::Messageing(QString chatType_t, QString chatName_t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Messageing)
{
    ui->setupUi(this);

    ui->Send_Button->setEnabled(false);

    chatType = chatType_t;
    chatName = chatName_t;

    //ConnectingCheck
    timer = new QTimer(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);

    //Client Creation
    client_t = new Client;
    client_t->readTokenFile();
    token = client_t->getToken();

}

Messageing::~Messageing()
{
    delete ui;
    delete timer;
    delete client_t;
}

//Files update and show contacts
void Messageing::gettingFromServer(){
    //getFromServer *serverGetter = new getFromServer;
    //serverGetter->runGetting();
    ui->recieve_textedit->clear();
    getFromFile *getter = new getFromFile;
    QString Groups("Groups");
    QString Channels("Channels");
    QString Users("Users");
    if(chatType == Groups){
        Lists = getter->getGroupChats(chatName);
        chatSize = getter->getGroupSize();
    }
    else if(chatType == Channels){
        Lists = getter->getChannelChats(chatName);
        chatSize = getter->getChannelSize();
    }
    else if(chatType == Users){
        Lists = getter->getUserChats(chatName);
        chatSize = getter->getUserSize();
    }

    for(int i = 0; i < chatSize; i++){
        ui->recieve_textedit->setText(ui->recieve_textedit->toPlainText() + "-" + Lists[0][i] + ": " + Lists[1][i] + "\n");
    }
    delete getter;
}



//ConnectionCheckFunction
void Messageing::ConnectionCheckFunc(){
    ConnectionCheck *c_t = new ConnectionCheck();
    forever{
        if(c_t->connectOrNot())
            ui->connecting_label->setText("Connected;))");
        else
            ui->connecting_label->setText("Connecting...");
        QThread::sleep(1);
    }
    delete c_t;
}

void Messageing::on_back_button_clicked()
{
    GeneralPage *generalpageForm = new GeneralPage;
    generalpageForm->show();
    close();
}

void Messageing::on_message_lineedit_textChanged()
{
    if(ui->message_lineedit->text().isEmpty()){
        ui->error_label->setText("*write message to send.");
        ui->Send_Button->setEnabled(false);
    }
    else{
        ui->error_label->setText("");
        ui->Send_Button->setEnabled(true);
    }
}

void Messageing::on_message_lineedit_editingFinished()
{
    messageText = ui->message_lineedit->text();
}

void Messageing::on_Send_Button_clicked()
{
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        QNetworkAccessManager *manager = new QNetworkAccessManager;
        QString request;
        if(chatType == "Users")
            request = "http://api.softserver.org:1104/sendmessageuser?token=" + token + "&dst=" + chatName + "&body=" + messageText;
        else if(chatType == "Groups")
            request = "http://api.softserver.org:1104/sendmessagegroup?token=" + token + "&dst=" + chatName + "&body=" + messageText;
        else if(chatType == "Channels")
            request = "http://api.softserver.org:1104/sendmessagechannel?token=" + token + "&dst=" + chatName + "&body=" + messageText;

        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(sendMessage(QNetworkReply *)));
        manager->get(QNetworkRequest(QUrl(request)));
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;
    //delete manager;

}

void Messageing::sendMessage(QNetworkReply *reply){
    JsonConverter *json = new JsonConverter;
    json->setJsonByte(reply->readAll());
    json->runJsonConverter();
    QVariantMap json_map = json->getJsonMap();
    delete json;

    //jsons are Like:
    //{"message": "Token is not Correct", "code": "401"}
    //{"message": "Message Sent Successfully", "code": "200"}
    //{"message": "You are not Admin of This Channel", "code": "404"}


    if(json_map["message"] == "Message Sent Successfully")
        ui->error_label->setText("Message Sent Successfully.");
    else if(json_map["message"] == "You are not Admin of This Channel")
        ui->error_label->setText("You are not Admin of This Channel!");
    else
        ui->error_label->setText("An error occured while sending message!");

    gettingFromServer();
}

//on refresh button
void Messageing::on_pushButton_clicked()
{
    gettingFromServer();
    QString Groups_t("Groups");
    QString Channels_t("Channels");
    QString Users("Users");
    if(chatType == Groups_t){
        Groups *goorop = new Groups;
        goorop->gettingFromServer();
    }
    else if(chatType == Channels_t){
        Channals *channeels = new Channals;
        channeels->gettingFromServer();
    }
    else if(chatType == Users){
        Contacts *kantact = new Contacts;
        kantact->gettingFromServer();
    }


}
