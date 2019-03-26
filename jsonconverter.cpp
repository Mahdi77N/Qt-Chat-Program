#include "jsonconverter.h"

/*void JsonConverter::setJsonText(QString j){
    json_text = j;
}*/
void JsonConverter::setJsonByte(QByteArray j){
    json_byte = j;
}

QVariantMap JsonConverter::getJsonMap(){
    return json_map;
}

void JsonConverter::runJsonConverter(){
    //json_byte = json_text.toLocal8Bit();
    json_doc = QJsonDocument::fromJson(json_byte);
    json_obj = json_doc.object();
    json_map = json_obj.toVariantMap();
}
