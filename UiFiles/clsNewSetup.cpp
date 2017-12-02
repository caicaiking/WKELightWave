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
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

}

int clsNewSetup::getChannel() const
{
    return this->channel;
}

void clsNewSetup::setChannel(int channel)
{
    this->cmbChannel->setCurrentIndex(channel-1);
}

void clsNewSetup::setMeter(QString meter)
{
   this->show();
   if(meter == "WK6500")
       on_btnLCR_clicked();
   else
       on_btnHV_clicked();
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
}

void clsNewSetup::on_btnLCR_clicked()
{
    channel=cmbChannel->currentIndex()+1;
    clsWK6500Meter *dlg=new clsWK6500Meter(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        this->meter="WK6500";
        QString tmpCondition=dlg->getCondition();
        QVariantMap conditionMap;
        QJsonDocument jsondocument;

        conditionMap.insert("channel", channel);
        conditionMap.insert("meter", meter);
        conditionMap.insert("conditions", tmpCondition);

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
        QString tmpCondition=dlg->getCondition();
        QVariantMap conditionMap;
        conditionMap.insert("channel",channel);
        conditionMap.insert("meter",meter);
        conditionMap.insert("conditions", tmpCondition);
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
