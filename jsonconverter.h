#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>

class JsonConverter
{
public:
    //void setJsonText(QString j);
    void setJsonByte(QByteArray j);
    QVariantMap getJsonMap();
    void runJsonConverter();

private:
    //QString json_text;
    QByteArray json_byte;
    QJsonDocument json_doc;
    QJsonObject json_obj;
    QVariantMap json_map;

};

#endif // JSONCONVERTER_H
