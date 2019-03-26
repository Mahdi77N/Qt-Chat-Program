#include "addcontact.h"
#include "ui_addcontact.h"
#include "generalpage.h"

addContact::addContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addContact)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
}

addContact::~addContact()
{
    delete ui;
}

void addContact::on_pushButton_2_clicked()
{
    GeneralPage *generalpageForm = new GeneralPage;
    generalpageForm->show();
    close();
}

void addContact::on_lineEdit_textChanged()
{
    if(ui->lineEdit->text().isEmpty()){
        ui->pushButton->setEnabled(false);
        ui->label->setText("*Username should be filled.");
    }
    else{
        ui->pushButton->setEnabled(true);
        ui->label->setText("");
    }
}

void addContact::on_lineEdit_editingFinished()
{
    username = ui->lineEdit->text();
}

void addContact::on_pushButton_clicked()
{
    ConnectionCheck *auth_c = new ConnectionCheck;
    if(auth_c->connectOrNot() == 1){
        QNetworkAccessManager *manager = new QNetworkAccessManager;
        Client c;
        c.readTokenFile();

        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(addContactSlot(QNetworkReply*)));
        QString request = "http://api.softserver.org:1104/sendmessageuser?token=" + c.getToken() + "&dst=" + username + "&body=" + "";
        manager->get(QNetworkRequest(QUrl(request)));
    }
    else{
        ui->label->setText("You are not to the Internet!");
    }
}

void addContact::addContactSlot(QNetworkReply *reply){
    JsonConverter *json = new JsonConverter;
    json->setJsonByte(reply->readAll());
    json->runJsonConverter();
    QVariantMap json_map = json->getJsonMap();
    delete json;

    //json messages are like:
    //{"message": "Destination User Not Found", "code": "404"}
    //{"message": "Message Sent Successfully", "code": "200"}
    //{"message": "Token is not Correct", "code": "401"}

    if(json_map["message"] == "Message Sent Successfully"){
        QMessageBox msg;
        msg.setText("Username added Successfully.");
        msg.exec();

        GeneralPage *generalpageForm = new GeneralPage;
        generalpageForm->show();
        close();
    }
    else if(json_map["message"] == "Destination User Not Found")
        ui->label->setText("User not found!");
    else
        ui->label->setText("An error occured while adding user!");
}
