#include "clsNewSetup.h"
#include "clsWK6500Meter.h"
#include "clsHightVoltage.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "publicUtility.h"
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

QString clsNewSetup::getMeter() const
{
    return meter;
}

void clsNewSetup::on_cmbChannel_currentIndexChanged(int index)
{
    this->channel=index+1;
    qDebug()<<" new "<<channel;
}

void clsNewSetup::on_btnLCR_clicked()
{
    channel=cmbChannel->currentIndex()+1;
    clsWK6500Meter *dlg=new clsWK6500Meter(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        this->meter="WK";
        QString tmpCondition=dlg->getCondtion();
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
                    conditionMap.insert("meter",meter);
                }
            }
        }
        jsondocument=QJsonDocument::fromVariant(conditionMap);
        if(!(jsondocument.isNull()))
        {
            condition=jsondocument.toJson();
        }
        this->accept();
    }
}

void clsNewSetup::on_btnHV_clicked()
{
    channel=cmbChannel->currentIndex()+1;
    clsHightVoltage *dlg=new clsHightVoltage(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        this->meter="HV";
        QString tmpCondition;
        tmpCondition=dlg->getCondition();
        QVariantMap conditionMap=publicUtility::parseConditions(tmpCondition);
        conditionMap.insert("channel",channel);
        conditionMap.insert("meter",meter);
        QJsonDocument jsondocument=QJsonDocument::fromVariant(conditionMap);
        if(!(jsondocument.isNull()))
        {
            condition=jsondocument.toJson();
        }

        this->accept();
    }
}

void clsNewSetup::on_btnCancel_clicked()
{
    this->reject();
}
