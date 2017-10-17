#include "clsNewSetup.h"
#include "clsWK6500Meter.h"
#include "clsHightVoltage.h"

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
}

void clsNewSetup::on_btnLCR_clicked()
{
    clsWK6500Meter *meter=new clsWK6500Meter(this);
    if(meter->exec()==QDialog::Accepted)
    {
        QString condition=meter->getCondtion();
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

//        QString tx=QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg(item21).arg(item22)
//                .arg(QString::number(freqency2)+"Hz").arg(QString::number(level2)+levelUnit2)
//                .arg(range2).arg(speed2).arg(equcct2).arg(QString::number(bias2)+biasType2)
//                .arg(biasSwitch2);
        channel=cmbChannel->currentIndex()+1;
        this->condition=meter->getCondtion();
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
