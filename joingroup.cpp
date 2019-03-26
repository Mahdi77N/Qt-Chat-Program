#include "joingroup.h"
#include "ui_joingroup.h"

joinGroup::joinGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::joinGroup)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager;

    //Disable join group button
    ui->join_button->setEnabled(false);

    //ConnectingCheck
    timer = new QTimer(0);
    connect(timer,SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);

    //ClientCreation
    client_t = new Client;
    client_t->readTokenFile();
    token = client_t->getToken();

}

joinGroup::~joinGroup()
{
    delete ui;
    delete timer;
    delete client_t;
    delete manager;
}


//ConnectionCheckFunction
void joinGroup::ConnectionCheckFunc(){
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

//on join group button
void joinGroup::on_join_button_clicked()
{
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        joingroupFunction();
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;
}


//join group Function
void joinGroup::joingroupFunction(){
    QString request = "http://api.softserver.org:1104/joingroup?token=" + token + "&group_name=" + name;
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(joingroupReply(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(request)));
}
void joinGroup::joingroupReply(QNetworkReply *reply){
    JsonConverter *json = new JsonConverter;
    json->setJsonByte(reply->readAll());
    json->runJsonConverter();
    QVariantMap json_map = json->getJsonMap();
    delete json;

    //joining group json messages are like:
    //{"message": "Token is not Correct", "code": "401"}
    //{"message": "Group Not Found", "code": "404"}
    //{"message": "Successfully Joined", "code": "200"}
    //{"message": "You are already Joined!", "code": "200"}

    if(json_map["message"] == "Successfully Joined"){
        QMessageBox msg;
        msg.setText("Successfully Joined.");
        msg.exec();

        GeneralPage *generalpageForm = new GeneralPage;
        generalpageForm->show();
        close();
    }
    else if(json_map["message"] == "Group Not Found")
        ui->error_label->setText("Group Not Found.");
    else if(json_map["message"] == "You are already Joined!")
        ui->error_label->setText("You are already Joined!");
    else
        ui->error_label->setText("An error occured while joining.");
}


//Check if name is filled
void joinGroup::on_group_name_textChanged()
{
    if(ui->group_name->text().isEmpty()){
        ui->join_button->setEnabled(false);
        ui->error_label->setText("*Group name should be filled.");
    }
    else{
        ui->join_button->setEnabled(true);
        ui->error_label->setText("");
    }
}


//Set name
void joinGroup::on_group_name_editingFinished()
{
    name = ui->group_name->text();
}
