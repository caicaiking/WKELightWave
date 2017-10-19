#include "clsNewSetup.h"
#include "clsWK6500Meter.h"
#include "clsHightVoltage.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

clsNewSetup::clsNewSetup(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

}

int clsNewSetup::getChannel() const
{
    return this->channel;
}

QString clsNewSetup::getCondtion() const
{
    return condition;
}

void clsNewSetup::on_cmbChannel_currentIndexChanged(int index)
{
    this->channel=index+1;
    qDebug()<<" new "<<channel;
}

void clsNewSetup::on_btnLCR_clicked()
{
    channel=cmbChannel->currentIndex()+1;
    clsWK6500Meter *meter=new clsWK6500Meter(this);
    if(meter->exec()==QDialog::Accepted)
    {
        QString tmpCondition=meter->getCondtion();
        QVariantMap conditionMap;
        QJsonParseError error;
        QJsonDocument jsondocument=QJsonDocument::fromJson(tmpCondition.toUtf8(),&error);
        if(error.error==QJsonParseError::NoError)
        {
            if(!(jsondocument.isNull() || jsondocument.isEmpty()))
            {
                if(jsondocument.isObject())
                {
                    conditionMap=jsondocument.toVariant().toMap();
                    conditionMap.insert("channel",channel);
                }
            }
        }
        jsondocument=QJsonDocument::fromVariant(conditionMap);
        if(!(jsondocument.isNull()))
        {
            condition=jsondocument.toJson();
        }

        //lcrCondition.replace(1,condition);
//        QVariantMap conditionMap=parseCondition(condition);
//        QString item21=conditionMap["item1"].toString();
//        QString item22=conditionMap["item2"].toString();
//        double freqency2=conditionMap["frequency"].toDouble();
//        double level2=conditionMap["level"].toDouble();
//        QString levelUnit2=conditionMap["levelUnit"].toString();
//        QString range2=conditionMap["range"].toString();
//        QString speed2=conditionMap["speed"].toString();
//        QString equcct2=conditionMap["equcct"].toString();
//        double bias2=conditionMap["bias"].toDouble();
//        QString biasType2=conditionMap["biasType"].toString();
//        QString biasSwitch2=conditionMap["biasSwitch"].toString();




//        this->condition=meter->getCondtion();
        this->accept();
    }
}

void clsNewSetup::on_btnHV_clicked()
{

}

void clsNewSetup::on_btnCancel_clicked()
{
    this->reject();
}
