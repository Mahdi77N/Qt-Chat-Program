#include "createchannal.h"
#include "ui_createchannal.h"

CreateChannal::CreateChannal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateChannal)
{
    ui->setupUi(this);
    
    manager = new QNetworkAccessManager;

    //DisableCreateChannalButton
    ui->create_channal->setEnabled(false);

    //title is empty
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

CreateChannal::~CreateChannal()
{
    delete ui;
    delete timer;
    delete client_t;
    delete manager;
}

//ConnectionCheckFunction
void CreateChannal::ConnectionCheckFunc(){
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


//OnCreateButtonChannal
void CreateChannal::on_create_channal_clicked()
{
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        createchannalFunction();
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;
}

//create channal function
void CreateChannal::createchannalFunction(){
    QString request;
    if(title_t == 0)
        request = "http://api.softserver.org:1104/createchannel?token=" + token + "&channel_name=" + name;
    else
        request = request = "http://api.softserver.org:1104/createchannel?token=" + token + "&channel_name=" + name + "&channel_title=" + title;


    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(createchannalReply(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(request)));
}
void CreateChannal::createchannalReply(QNetworkReply *reply){
    JsonConverter *createchannal_json = new JsonConverter;
    createchannal_json->setJsonByte(reply->readAll());
    createchannal_json->runJsonConverter();
    QVariantMap json_map = createchannal_json->getJsonMap();
    delete createchannal_json;

    //create channal json is like:
    //{"message": "token is not Correct", "code": "401"}
    //{"message": "Channel Created Successfully", "code": "200"}
    //{"message": "Channel_name Exist Try Another!", "code": "204"}

    if(json_map["message"] == "Channel Created Successfully"){
        QMessageBox msg;
        msg.setText("Channel Created Successfully.");
        msg.exec();

        GeneralPage *generalpageForm = new GeneralPage;
        generalpageForm->show();
        close();
    }
    else if(json_map["message"] == "Channel_name Exist Try Another!")
        ui->error_label->setText("Channel Name Exist Try Another!");
    else
        ui->error_label->setText("An error occured while creating channal.");

}


//Check if channal name is filled
void CreateChannal::on_channal_name_textChanged()
{
    if(ui->channal_name->text().isEmpty()){
        ui->create_channal->setEnabled(false);
        ui->error_label->setText("*Channal name should be filled.");
    }
    else{
        ui->create_channal->setEnabled(true);
        ui->error_label->setText("");
    }
}
void CreateChannal::on_channal_title_textChanged()
{
    if(ui->channal_name->text().isEmpty()){
        ui->create_channal->setEnabled(false);
        ui->error_label->setText("*Channal name should be filled.");
    }
    else{
        ui->create_channal->setEnabled(true);
        ui->error_label->setText("");
    }
}

//Back to general page
void CreateChannal::on_cancel_button_clicked()
{
    GeneralPage *generalpageForm = new GeneralPage;
    generalpageForm->show();
    close();
}

//Set title
void CreateChannal::on_channal_title_editingFinished()
{
    if(ui->channal_name->text().isEmpty())
        title_t = 0;
    else{
        title = ui->channal_title->text();
        title_t = 1;
    }
}

//Set name
void CreateChannal::on_channal_name_editingFinished()
{
    name = ui->channal_name->text();
}


