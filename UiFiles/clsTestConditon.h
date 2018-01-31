#ifndef CLSTESTCONDITON_H
#define CLSTESTCONDITON_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariantMap>
#include <QPoint>

class clsTestConditons
{
public:
    QPoint channel;
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
      int channelStart = map["channelStart"].toInt();
        int channelStop = map["channelStop"].toInt();
        channel.setX(channelStart);
        channel.setY(channelStop);
        condition = map["conditions"].toString();
        meter = map["meter"].toString();


    }
    QString toJson()
    {
        QVariantMap map;
        map.insert("channelStart", this->channel.x());
        map.insert("channelStop", this->channel.y());
        map.insert("conditions", this->condition);
        map.insert("meter",this->meter);
        QJsonDocument jsDocument = QJsonDocument::fromVariant(map);
        return jsDocument.toJson(QJsonDocument::Indented);
    }
};


#endif // CLSTESTCONDITON_H
