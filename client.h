#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

class Client
{
public:
    void setStatus(int a);
    int getStatus();

    void setToken(QString a);
    QString getToken();

    void setUsername(QString a);
    QString getUsername();

    void setPassword(QString a);
    QString getPassword();

    void readStatusFile();
    void readTokenFile();
    void readPassword();
    void readUsername();

    void writeTokenFile();
    void writeStatusFile();
    void writePassword();
    void writeUsername();

private:
    int status;
    QString token;
    QString username;
    QString password;


};

#endif // CLIENT_H
