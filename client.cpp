#include "client.h"


void Read(QString );

void Client::setStatus(int a)
{
    status = a;
}

int Client::getStatus()
{
    return status;
}

void Client::setToken(QString a)
{
    token = a;
}

QString Client::getToken()
{
    return token;
}

void Client::setUsername(QString a)
{
    username = a;
}

QString Client::getUsername()
{
    return username;
}

void Client::setPassword(QString a)
{
    password = a;
}

QString Client::getPassword()
{
    return password;
}

void Client::readStatusFile()
{
    QFile MyFile(QString("E:/Programming/AP Project/Texts/Status.txt"));
    if(!MyFile.open((QFile::ReadOnly | QFile::Text))){
        QMessageBox msgbox;
        msgbox.setText("An error occured while opening file.");
        msgbox.exec();
        exit(0);
    }
    QTextStream in(&MyFile);
    QString MyText = in.readAll();
    status = MyText.toInt();
    MyFile.close();
}

void Client::readTokenFile()
{
    QFile MyFile(QString("E:/Programming/AP Project/Texts/Token.txt"));
    if(!MyFile.open((QFile::ReadOnly | QFile::Text))){
        QMessageBox msgbox;
        msgbox.setText("An error occured while opening file.");
        msgbox.exec();
        exit(0);
    }
    QTextStream in(&MyFile);
    QString MyText = in.readAll();
    token = MyText;
    MyFile.close();
}

void Client::readPassword()
{
    QFile MyFile(QString("E:/Programming/AP Project/Texts/Password.txt"));
    if(!MyFile.open((QFile::ReadOnly | QFile::Text))){
        QMessageBox msgbox;
        msgbox.setText("An error occured while opening file.");
        msgbox.exec();
        exit(0);
    }
    QTextStream in(&MyFile);
    QString MyText = in.readAll();
    password = MyText;
    MyFile.close();
}

void Client::readUsername()
{
    QFile MyFile(QString("E:/Programming/AP Project/Texts/Username.txt"));
    if(!MyFile.open((QFile::ReadOnly | QFile::Text))){
        QMessageBox msgbox;
        msgbox.setText("An error occured while opening file.");
        msgbox.exec();
        exit(0);
    }
    QTextStream in(&MyFile);
    QString MyText = in.readAll();
    username = MyText;
    MyFile.close();
}

void Client::writeStatusFile()
{
    QFile MyFile(QString("E:/Programming/AP Project/Texts/Status.txt"));
    if(!MyFile.open((QFile::WriteOnly | QFile::Text))){
        QMessageBox msgbox;
        msgbox.setText("An error occured while opening file.");
        msgbox.exec();
        exit(0);
    }
    QTextStream out(&MyFile);
    out << status;
    MyFile.flush();
    MyFile.close();
}

void Client::writeTokenFile()
{
    QFile MyFile(QString("E:/Programming/AP Project/Texts/Token.txt"));
    if(!MyFile.open((QFile::WriteOnly | QFile::Text))){
        QMessageBox msgbox;
        msgbox.setText("An error occured while opening file.");
        msgbox.exec();
        exit(0);
    }
    QTextStream out(&MyFile);
    out << token;
    MyFile.flush();
    MyFile.close();
}

void Client::writeUsername()
{
    QFile MyFile(QString("E:/Programming/AP Project/Texts/Username.txt"));
    if(!MyFile.open((QFile::WriteOnly | QFile::Text))){
        QMessageBox msgbox;
        msgbox.setText("An error occured while opening file.");
        msgbox.exec();
        exit(0);
    }
    QTextStream out(&MyFile);
    out << username;
    MyFile.flush();
    MyFile.close();
}

void Client::writePassword()
{
    QFile MyFile(QString("E:/Programming/AP Project/Texts/Password.txt"));
    if(!MyFile.open((QFile::WriteOnly | QFile::Text))){
        QMessageBox msgbox;
        msgbox.setText("An error occured while opening file.");
        msgbox.exec();
        exit(0);
    }
    QTextStream out(&MyFile);
    out << password;
    MyFile.flush();
    MyFile.close();
}
