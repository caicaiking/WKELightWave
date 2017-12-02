#ifndef CLSTESTCONDITON_H
#define CLSTESTCONDITON_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariantMap>
class clsTestConditons
{
public:
    int channel;
    QString condition;
    QString meter;
    void setJson(QString str)
    {
        QJsonDocument jsDocument;
        QJsonParseError error;

        jsDocument = QJsonDocument::fromJson(str.toUtf8(),&error);

        if(error.error != QJsonParseError::NoError)
            return;

        if(jsDocument.isEmpty() || jsDocument.isNull())
            return;

        QVariantMap map = jsDocument.toVariant().toMap();
        channel = map["channel"].toInt();
        condition = map["conditions"].toString();
        meter = map["meter"].toString();


    }
    QString toJson()
    {
        QVariantMap map;
        map.insert("channel", this->channel);
        map.insert("conditions", this->condition);
        map.insert("meter",this->meter);
        QJsonDocument jsDocument = QJsonDocument::fromVariant(map);
        return jsDocument.toJson(QJsonDocument::Indented);
    }
};


#endif // CLSTESTCONDITON_H
