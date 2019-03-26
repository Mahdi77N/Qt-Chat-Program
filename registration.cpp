#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager;

    //Firstname and Lastname is Empty
    firstname_t = 0;
    lastname_t = 0;

    //Disable signup button
    ui->register_button->setEnabled(false);

    //Connecting check label
    timer = new QTimer(0);
    connect(timer,SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(10000);

}

Registration::~Registration()
{
    delete ui;
    delete timer;
    delete manager;

}

//On Register Button Click Function
void Registration::on_register_button_clicked()
{
    ConnectionCheck *c_auth = new ConnectionCheck();
    if(c_auth->connectOrNot() == 1){
        signupFunction();
    }
    else
        ui->error_label->setText("You are not Connected to Internet.");
    delete c_auth;
}

//Signup Function
void Registration::signupFunction(){
    //Signup request Infos String
    QString req_str;
    if(firstname_t == 1 && lastname_t == 1)
        req_str = "http://api.softserver.org:1104/signup?username=" + username + "&password=" + password + "&firstname=" + firstname + "&lastname=" + lastname;
    else if(firstname_t == 1 && lastname_t == 0)
        req_str = "http://api.softserver.org:1104/signup?username=" + username + "&password=" + password + "&firstname=" + firstname;
    else if(firstname_t == 0 && lastname_t == 1)
        req_str = "http://api.softserver.org:1104/signup?username=" + username + "&password=" + password + "&lastname=" + lastname;
    else
        req_str = "http://api.softserver.org:1104/signup?username=" + username + "&password=" + password;

    //CreateAndSendSignupRequestToServer
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(signupNetworkReply(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(req_str)));
}

void Registration::signupNetworkReply(QNetworkReply *reply){
    JsonConverter *signup_json = new JsonConverter;
    signup_json->setJsonByte(reply->readAll());
    signup_json->runJsonConverter();
    QVariantMap signup_map_t = signup_json->getJsonMap();
    delete signup_json;

    //signup json form is like :
    //{"message": "User Exist Try Another!", "code": "204"}
    //{"message": "Signed Up Successfully", "code": "200"}

    if(signup_map_t["message"] == "User Exist Try Another!"){
        ui->error_label->setText("User Exist Try Another!");
    }
    else if(signup_map_t["message"] == "Signed Up Successfully"){
        ui->error_label->setText("Signed Up Successfully ->>> Now Go And Sign in ;)))");
    }
    else
        ui->error_label->setText("An error occured while registeration.");

}


//ConnectionCheckFunction
void Registration::ConnectionCheckFunc(){
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


//Set firstname
void Registration::on_firstname_text_editingFinished()
{
    firstname = ui->firstname_text->text();
}

//Set lastname
void Registration::on_lastname_text_editingFinished()
{
    lastname = ui->lastname_text->text();
}

//Set username
void Registration::on_username_text_editingFinished()
{
    username = ui->username_text->text();
}

//Set password
void Registration::on_password_text_editingFinished()
{
    password = ui->password_text->text();
}

//CheckIfPasswordAndUsernameFeildAreFilled
void Registration::onTextChanged(){
    if(ui->password_text->text().isEmpty() || ui->username_text->text().isEmpty()){
        ui->register_button->setEnabled(false);
        ui->error_label->setText("*Username and Password should be filled.");
    }
    else
        ui->register_button->setEnabled(true);
}
void Registration::on_username_text_textChanged()
{
    onTextChanged();
}
void Registration::on_password_text_textChanged()
{
    onTextChanged();
}

//Check if firstname is filled
void Registration::on_firstname_text_textChanged()
{
    if(ui->firstname_text->text().isEmpty())
        firstname_t = 0;
    else
        firstname_t = 1;
}

//Check if lastname is filled
void Registration::on_lastname_text_textChanged()
{
    if(ui->lastname_text->text().isEmpty())
        lastname_t = 0;
    else
        lastname_t = 1;
}

void Registration::on_pushButton_clicked()
{
    authorization *signinForm = new authorization;
    signinForm->show();
    close();
}
