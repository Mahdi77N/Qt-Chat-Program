#include "contacts.h"
#include "ui_contacts.h"

Contacts::Contacts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contacts)
{
    ui->setupUi(this);

    //Disable Ok
    ui->search_button->setEnabled(false);


    //ConnectingCheck
    timer = new QTimer(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);


}

Contacts::~Contacts()
{
    delete ui;
    delete timer;

}

//Files update and show contacts
void Contacts::gettingFromServer(){
    //getFromServer *serverGetter = new getFromServer;
    //serverGetter->runGetting();
    ui->contacts_name->clear();
    getFromFile *getter = new getFromFile;
    Lists = getter->getUserList();
    userSize = getter->getUserSize();
    for(int i = 0; i < userSize; i++){
        ui->contacts_name->setText(ui->contacts_name->toPlainText() + Lists[i] + "\n");
    }
    //delete serverGetter;
    delete getter;
}

//ConnectionCheckFunction
void Contacts::ConnectionCheckFunc(){
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

//Back Button
void Contacts::on_back_button_clicked()
{
    GeneralPage *generalpageForm = new GeneralPage;
    generalpageForm->show();
    close();
}

void Contacts::on_search_button_clicked()
{
    if(!checkExistance(contact)){
        ui->error_label->setText("*No matching Contact name found.");
    }
    else{
        ui->error_label->setText("");
        Messageing *messengerForm = new Messageing("Users", contact);
        messengerForm->show();
        close();
    }
}

void Contacts::on_contact_name_textChanged()
{
    if(ui->contact_name->text().isEmpty()){
        ui->error_label->setText("*Contact name feild should be filled.");
        ui->search_button->setEnabled(false);
    }
    else{
        ui->error_label->setText("");
        ui->search_button->setEnabled(true);
    }
}

void Contacts::on_contact_name_editingFinished()
{
    contact = ui->contact_name->text();

}

bool Contacts::checkExistance(QString s){
    for(int i = 0; i < userSize; i++){
        if(s == Lists[i]){
            return true;
        }
    }
    return false;
}


//on refresh button
void Contacts::on_pushButton_clicked()
{
    gettingFromServer();
}
