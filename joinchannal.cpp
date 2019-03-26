#include "joinchannal.h"
#include "ui_joinchannal.h"

joinChannal::joinChannal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::joinChannal)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager;

    //Disable join channal button
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

joinChannal::~joinChannal()
{
    delete ui;
    delete timer;
    delete client_t;
    delete manager;
}


//ConnectionCheckFunction
void joinChannal::ConnectionCheckFunc(){
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

//join channal button
void joinChannal::on_join_button_clicked()
{
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        joinchannalFunction();
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;
}

//join channal Function
void joinChannal::joinchannalFunction(){
    QString request = "http://api.softserver.org:1104/joinchannel?token=" + token + "&channel_name=" + name;
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(joinchannalReply(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(request)));
}
void joinChannal::joinchannalReply(QNetworkReply *reply){
    JsonConverter *json = new JsonConverter;
    json->setJsonByte(reply->readAll());
    json->runJsonConverter();
    QVariantMap json_map = json->getJsonMap();
    delete json;

    //join channal messages are like:
    //{"message": "Token is not Correct", "code": "401"}
    //{"message": "Channel Not Found", "code": "404"}
    //{"message": "Successfully Joined", "code": "200"}
    //{"message": "You are already Joined!", "code": "200"}
    if(json_map["message"] == "Channel Not Found")
        ui->error_label->setText("Channel Not Found.");
    else if(json_map["message"] == "Successfully Joined"){
        QMessageBox msg;
        msg.setText("Successfully Joined.");
        msg.exec();

        GeneralPage *generalpageForm = new GeneralPage;
        generalpageForm->show();
        close();
    }
    else if(json_map["message"] == "You are already Joined!")
        ui->error_label->setText("You are already Joined!");
    else
        ui->error_label->setText("An error occured while joining.");
}


//Back button back to general page
void joinChannal::on_back_button_clicked()
{
    GeneralPage *generalpageForm = new GeneralPage;
    generalpageForm->show();
    close();
}

//Check if channal name is filled
void joinChannal::on_channal_name_textChanged()
{
    if(ui->channal_name->text().isEmpty()){
        ui->join_button->setEnabled(false);
        ui->error_label->setText("*Group name should be filled.");
    }
    else{
        ui->join_button->setEnabled(true);
        ui->error_label->setText("");
    }
}

//Set name
void joinChannal::on_channal_name_editingFinished()
{
    name = ui->channal_name->text();
}
