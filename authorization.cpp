#include "authorization.h"
#include "ui_authorization.h"

authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager;

    //DisableSigninButton
    ui->signIn_button->setEnabled(false);

    //ConnectingCheck
    timer = new QTimer(0);
    connect(timer,SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);

    //ClientCreation
    client_t = new Client;

}

authorization::~authorization()
{
    delete ui;
    delete timer;
    delete client_t;
    delete manager;

}

//SignupButtonFunction
void authorization::on_signUp_button_clicked()
{
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        Registration *registerForm = new Registration;
        registerForm->show();
        close();
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;

}

//SigninButtonFunction
void authorization::on_signIn_button_clicked()
{
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        signinFunction();
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;
}

//SigninFunction
void authorization::signinFunction(){
    //CreateAndSendSigninRequestToServer
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(signinNetworkReply(QNetworkReply*)));
    QString request = "http://api.softserver.org:1104/login?username=" + username + "&password=" + password;
    manager->get(QNetworkRequest(QUrl(request)));
}
void authorization::signinNetworkReply(QNetworkReply *reply){
    JsonConverter *signin_json = new JsonConverter;
    signin_json->setJsonByte(reply->readAll());
    signin_json->runJsonConverter();
    QVariantMap json_map_t = signin_json->getJsonMap();
    delete signin_json;

    //signin json form is like :
    //{"message": "Password is not Correct", "code": "401"}
    //{"message": "User Not Found", "code": "404"}
    //{"message": "Logged in Successfully", "code": "200", "token": "437df3b83d8fcca063b7c5df949cc271"}
    //{"message": "You are already logged in!", "code": "200"}

    if(json_map_t["message"].toString() == "Password is not Correct"){
        ui->error_label2->setText("Wrong Password.");
    }
    else if(json_map_t["message"].toString() == "User Not Found"){
        ui->error_label2->setText("Username Not Found.");
    }
    else if(json_map_t["message"].toString() == "Logged in Successfully"){
        client_t->setToken(json_map_t["token"].toString());
        client_t->writeTokenFile();
        client_t->setStatus(1);
        client_t->writeStatusFile();
        GeneralPage *GeneralPageForm = new GeneralPage;
        GeneralPageForm->show();
        close();
    }
    else
        ui->error_label2->setText("An error occured while sign in.");

}

//ConnectionCheckFunction
void authorization::ConnectionCheckFunc(){
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

//CheckIfAllFeildsAreFillOrNot
void authorization::onTextChanged(){
    if(ui->username_text->text().isEmpty() || ui->password_text->text().isEmpty()){
        ui->signIn_button->setEnabled(false);
        ui->error_label2->setText("*All feilds should be filled.");
    }
    else{
        ui->signIn_button->setEnabled(true);
        ui->error_label2->setText("");
    }
}
//CheckingFillingFeilds
void authorization::on_username_text_textChanged()
{
    onTextChanged();
}
void authorization::on_password_text_textChanged()
{
    onTextChanged();
}

void authorization::on_username_text_editingFinished()
{
    username = ui->username_text->text();
    client_t->setUsername(username);
    client_t->writeUsername();
}

void authorization::on_password_text_editingFinished()
{
    password = ui->password_text->text();
    client_t->setPassword(password);
    client_t->writePassword();
}
