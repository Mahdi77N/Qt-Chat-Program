#include "creategroupe.h"
#include "ui_creategroupe.h"

CreateGroupe::CreateGroupe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupe)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager;

    //Disable create button
    ui->create_group->setEnabled(false);

    //group title is empty
    title_t = 0;

    //ConnectingCheck
    timer = new QTimer(0);
    connect(timer,SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);

    //ClientCreation
    client_t = new Client;
    client_t->readTokenFile();
    token = client_t->getToken();


}

CreateGroupe::~CreateGroupe()
{
    delete ui;
    delete timer;
    delete client_t;
    delete manager;
}

//ConnectionCheckFunction
void CreateGroupe::ConnectionCheckFunc(){
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


//On create group button
void CreateGroupe::on_create_group_clicked()
{
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        creategroupFunction();
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;
}

//Create group Function
void CreateGroupe::creategroupFunction(){
    QString request;
    if(title_t == 0)
        request = "http://api.softserver.org:1104/creategroup?token=" + token + "&group_name=" + name;
    else
        request = "http://api.softserver.org:1104/creategroup?token=" + token + "&group_name=" + name + "&group_title=" + title;

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(creategroupReply(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(request)));
}
void CreateGroupe::creategroupReply(QNetworkReply *reply){
    JsonConverter *json = new JsonConverter;
    json->setJsonByte(reply->readAll());
    json->runJsonConverter();
    QVariantMap json_map = json->getJsonMap();
    delete json;

    //create group messages are like:
    //{"message": "token is not Correct", "code": "401"}
    //{"message": "Group Created Successfully", "code": "200"}
    //{"message": "Group_name Exist Try Another!", "code": "204"}

    if(json_map["message"] == "Group Created Successfully"){
        QMessageBox msg;
        msg.setText("Group Created Successfully.");
        msg.exec();

        GeneralPage *generalpageForm = new GeneralPage;
        generalpageForm->show();
        close();
    }
    else if(json_map["message"] == "Group_name Exist Try Another!")
        ui->error_label->setText("Group Name Exist Try Another!");
    else
        ui->error_label->setText("An error occured while creating group.");
}

//set Title
void CreateGroupe::on_group_title_editingFinished()
{
    if(ui->group_title->text().isEmpty()){
        title_t = 0;
    }
    else{
        title_t = 1;
        title = ui->group_title->text();
    }
}

//set name
void CreateGroupe::on_group_name_editingFinished()
{
    name = ui->group_name->text();
}

//cancel button -> back to general page
void CreateGroupe::on_c_clicked()
{
    GeneralPage *generalpageForm = new GeneralPage;
    generalpageForm->show();
    close();
}


//Check if name is filled
void CreateGroupe::on_group_name_textChanged()
{
    if(ui->group_name->text().isEmpty()){
        ui->create_group->setEnabled(false);
        ui->error_label->setText("*Group name should be filled.");
    }
    else{
        ui->create_group->setEnabled(true);
        ui->error_label->setText("");
    }
}
void CreateGroupe::on_group_title_textChanged()
{
    if(ui->group_title->text().isEmpty())
        title_t = 0;
    else{
        title = ui->group_title->text();
        title_t = 1;
    }
}


