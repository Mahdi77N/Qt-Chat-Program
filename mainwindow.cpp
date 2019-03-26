#include "mainwindow.h"
#include <QMessageBox>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ConnectingLabelCheck
    //ConnectionCheckFunc();
    timer = new QTimer(0);
    connect(timer,SIGNAL(timeout()), this, SLOT(ConnectionCheckFunc()));
    timer->start(0);


    //ClientCreation
    client_t = new Client;
    client_t->readStatusFile();

    /*int t = client_t->getStatus();
    QMessageBox msn;
    msn.setText(QString::number(t));
    msn.exec();*/

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;

}

//StartBottonFunctions
void MainWindow::on_startButton_clicked()
{
    if(client_t->getStatus() == 1){
        GeneralPage *GeneralPageForm = new GeneralPage;
        GeneralPageForm->show();
        close();
    }
    else{
        ConnectionCheck *c_auth = new ConnectionCheck();
        if(c_auth->connectOrNot() == 1){
            authorization *startForm = new authorization;
            startForm->show();
            close();
        }
        else
            ui->error_label->setText("You are not Connected to Internet.");
        delete c_auth;
    }
}

//FunctionForConnectionCheckLabel
void MainWindow::ConnectionCheckFunc(){
    ConnectionCheck *c_t = new ConnectionCheck();
    forever{
        if(c_t->connectOrNot() == 1)
            ui->connecting_label->setText("Connected;))");
        else
            ui->connecting_label->setText("Connecting...");
        QThread::sleep(1);
    }
    delete c_t;
}
