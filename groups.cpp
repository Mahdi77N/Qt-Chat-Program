#include "groups.h"
#include "ui_groups.h"

Groups::Groups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Groups)
{
    ui->setupUi(this);

    //Disable Ok
    ui->search_button->setEnabled(false);


    //ConnectingCheck
    timer = new QTimer(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);
}

Groups::~Groups()
{
    delete ui;
    delete timer;
}


//Files update and show contacts
void Groups::gettingFromServer(){
    //getFromServer *serverGetter = new getFromServer;
    //serverGetter->runGetting();
    ui->groups_name->clear();
    getFromFile *getter = new getFromFile;
    Lists = getter->getGroupList();
    groupSize = getter->getGroupSize();
    for(int i = 0; i < groupSize; i++){
        ui->groups_name->setText(ui->groups_name->toPlainText() + Lists[i] + "\n");
    }
    //delete serverGetter;
    delete getter;
}

//ConnectionCheckFunction
void Groups::ConnectionCheckFunc(){
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
//on back button click
void Groups::on_back_button_clicked()
{
    GeneralPage *generalpageForm = new GeneralPage;
    generalpageForm->show();
    close();
}

void Groups::on_search_button_clicked()
{
    if(!checkExistance(contact)){
        ui->error_label->setText("*No matching Contact name found.");
    }
    else{
        ui->error_label->setText("");
        Messageing *messengerForm = new Messageing("Groups", contact);
        messengerForm->show();
        close();
    }
}

void Groups::on_group_name_textChanged()
{
    if(ui->group_name->text().isEmpty()){
        ui->error_label->setText("*Group name feild should be filled.");
        ui->search_button->setEnabled(false);
    }
    else{
        ui->error_label->setText("");
        ui->search_button->setEnabled(true);
    }
}

void Groups::on_group_name_editingFinished()
{
    contact = ui->group_name->text();
}

bool Groups::checkExistance(QString s){
    for(int i = 0; i < groupSize; i++){
        if(s == Lists[i]){
            return true;
        }
    }
    return false;
}


//on refresh button
void Groups::on_pushButton_clicked()
{
    gettingFromServer();
}
