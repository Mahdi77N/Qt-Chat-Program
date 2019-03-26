#include "generalpage.h"
#include "ui_generalpage.h"
#include "addcontact.h"

GeneralPage::GeneralPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralPage)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager;

    //ConnectingCheck
    timer = new QTimer(0);
    connect(timer,SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);

    //ClientCreation
    client_t = new Client;
    client_t->readStatusFile();
    client_t->readTokenFile();

    //Server Get file Everytime
    //server_connection_timer = new QTimer(0);
    //connect(server_connection_timer, SIGNAL(timeout()), this, SLOT(serverConnectionGetFile()));
    //server_connection_timer->start(1);






}

GeneralPage::~GeneralPage()
{
    delete ui;
    delete timer;
    delete client_t;
    delete manager;
    //delete server_connection_timer;

}

//ConnectionCheckFunction
void GeneralPage::ConnectionCheckFunc(){
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


//Server Connection get file Function
void GeneralPage::serverConnectionGetFile(){
    //Get All thing from Server
   // getFromServer *serverGetter = new getFromServer;
    //serverGetter->runGetting();
    //delete serverGetter;
}

void GeneralPage::on_contacts_button_clicked()
{
    //Get All thing from Server
    getFromServer *serverGetter = new getFromServer;
    serverGetter->runGetting();
    //QThread::sleep(1);
    Contacts *contactsForm = new Contacts;
    contactsForm->show();
    close();
}



void GeneralPage::on_groups_button_clicked()
{
    //Get All thing from Server
    getFromServer *serverGetter = new getFromServer;
    serverGetter->runGetting();
    //QThread::sleep(1);
    Groups *groupsForm = new Groups;
    groupsForm->show();
    close();
}



void GeneralPage::on_channals_button_clicked()
{
    //Get All thing from Server
    getFromServer *serverGetter = new getFromServer;
    serverGetter->runGetting();
    //QThread::sleep(1);
    Channals *channelsForm = new Channals;
    channelsForm->show();
    close();
}

void GeneralPage::on_addContact_button_clicked()
{
    addContact *addcontactForm = new addContact;
    addcontactForm->show();
    close();
}

void GeneralPage::on_joinGroup_button_clicked()
{
    joinGroup *joingroupForm = new joinGroup;
    joingroupForm->show();
    close();
}

void GeneralPage::on_joinChannal_button_clicked()
{
    joinChannal *joinchannalForm = new joinChannal;
    joinchannalForm->show();
    close();
}

void GeneralPage::on_createGroup_button_clicked()
{
    CreateGroupe *creategroupeForm = new CreateGroupe;
    creategroupeForm->show();
    close();
}

void GeneralPage::on_createChannal_button_clicked()
{
    CreateChannal *createchannalForm = new CreateChannal;
    createchannalForm->show();
    close();
}

//Logout Function
void GeneralPage::on_logout_button_clicked()
{
    //Get username and password from files
    QString username;
    QString password;
    client_t->readPassword();
    password = client_t->getPassword();
    client_t->readUsername();
    username = client_t->getUsername();
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        //Send request
        QString request = "http://api.softserver.org:1104/logout?username=" + username + "&password=" + password;
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(logoutReply(QNetworkReply*)));
        manager->get(QNetworkRequest(QUrl(request)));
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;
}
void GeneralPage::logoutReply(QNetworkReply *reply){
    JsonConverter *logout_json = new JsonConverter;
    logout_json->setJsonByte(reply->readAll());
    logout_json->runJsonConverter();
    QVariantMap json_map_t = logout_json->getJsonMap();
    delete logout_json;

    //logout json form is like :
    //{"message": "Password is not Correct", "code": "401"}
    //{"message": "User Not Found", "code": "404"}
    //{"message": "Logged Out Successfully", "code": "200"}
    //{"message": "You Have not Logged in Yet!", "code": "200"}
    if(json_map_t["message"].toString() == "Logged Out Successfully"){
        QMessageBox msg;
        msg.setText("Logged Out Successfully.");
        msg.exec();

        //Clear Files
        client_t->setStatus(0);
        client_t->writeStatusFile();
        client_t->setToken("");
        client_t->writeTokenFile();
        client_t->setPassword("");
        client_t->writePassword();
        client_t->setUsername("");
        client_t->writeUsername();

        //Signin Form
        authorization *signinForm = new authorization;
        signinForm->show();
        close();
    }
    else{
        close();
        QMessageBox msg;
        msg.setText("An error occured while sign in.");
        msg.exec();
    }

}
