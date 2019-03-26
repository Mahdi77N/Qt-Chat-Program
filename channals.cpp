#include "channals.h"
#include "ui_channals.h"

Channals::Channals(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Channals)
{
    ui->setupUi(this);

    //Disable Ok
    ui->search_button->setEnabled(false);


    //ConnectingCheck
    timer = new QTimer(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);

}

Channals::~Channals()
{
    delete ui;
    delete timer;

}

//Files update and show contacts
void Channals::gettingFromServer(){
    //getFromServer *serverGetter = new getFromServer;
    //serverGetter->runGetting();
    ui->channals_name->clear();
    getFromFile *getter = new getFromFile;
    Lists = getter->getChannelList();
    channelSize = getter->getChannelSize();
    for(int i = 0; i < channelSize; i++){
        ui->channals_name->setText(ui->channals_name->toPlainText() + Lists[i] + "\n");
    }
    //delete serverGetter;
    delete getter;
}

//ConnectionCheckFunction
void Channals::ConnectionCheckFunc(){
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
void Channals::on_back_button_clicked()
{
    GeneralPage *generalpageForm = new GeneralPage;
    generalpageForm->show();
    close();
}

void Channals::on_search_button_clicked()
{
    if(!checkExistance(contact)){
        ui->error_label->setText("*No matching Contact name found.");
    }
    else{
        ui->error_label->setText("");
        Messageing *messengerForm = new Messageing("Channels", contact);
        messengerForm->show();
        close();
    }
}

void Channals::on_channal_name_textChanged()
{
    if(ui->channal_name->text().isEmpty()){
        ui->error_label->setText("*Channel name feild should be filled.");
        ui->search_button->setEnabled(false);
    }
    else{
        ui->error_label->setText("");
        ui->search_button->setEnabled(true);
    }
}

void Channals::on_channal_name_editingFinished()
{
    contact = ui->channal_name->text();
}

bool Channals::checkExistance(QString s){
    for(int i = 0; i < channelSize; i++){
        if(s == Lists[i]){
            return true;
        }
    }
    return false;
}

//on refresh button
void Channals::on_pushButton_clicked()
{
    gettingFromServer();
}
