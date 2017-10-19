#include "clsChannelSettings.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

clsChannelSettings::clsChannelSettings(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    connect(labelClose,SIGNAL(labelClicked()),this,SLOT(onLabelCloseClicked()));
}

void clsChannelSettings::setChannel(const int channel)
{
    this->channel=channel;
}

void clsChannelSettings::setCondition(const QString condition)
{
    this->condition=condition;
    QJsonParseError error;
    QJsonDocument jsonDocument=QJsonDocument::fromJson(this->condition.toUtf8(),&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!(jsonDocument.isEmpty() || jsonDocument.isEmpty()))
        {
            if(jsonDocument.isObject())
            {
                QVariantMap conditionMap=jsonDocument.toVariant().toMap();
                this->item1=conditionMap["item1"].toString();
                this->item2=conditionMap["item2"].toString();
                this->frequency=conditionMap["frequency"].toDouble();
                this->level=conditionMap["level"].toDouble();
                this->levelUnit=conditionMap["levelUnit"].toString();
                this->range=conditionMap["range"].toString();
                this->speed=conditionMap["speed"].toString();
                this->equcct=conditionMap["equcct"].toString();
                this->bias=conditionMap["bias"].toDouble();
                this->biasSwitch=conditionMap["biasSwitch"].toString();
                this->biasType=conditionMap["biasType"].toString();
                this->item1HiLimit=conditionMap["item1HiLimit"].toDouble();
                this->item1LowLimit=conditionMap["item1LowLimit"].toDouble();
                this->item2HiLimit=conditionMap["item2HiLimit"].toDouble();
                this->item2LowLimit=conditionMap["item2LowLimit"].toDouble();
                this->channel=conditionMap["channel"].toInt();
            }
        }
    }
}

void clsChannelSettings::updateLabels()
{
    QStringList colorList;
    colorList<<"#D891EF"<<"#FFBF00"<<"#00FFFF"<<"#FDEE00"<<"#D0FF14"<<"#D19FE8"
            <<"#FA6E79"<<"#FE6F5E"<<"#ACE5EE"<<"#66FF00"<<"#FF007F"<<"#84DE02"<<"#1F75FE"
           <<"#08E8DE"<<"#FFAA1D"<<"#FF55A3"<<"#FF033E"<<"#FF2052"<<"#E0218A"<<"#ACE5EE";
    QList<QLabel*> labelList;
    QList<QLabel*> labelList1;
    labelList<<labelBias<<labelEqucct<<labelFreq<<labelLevel<<labelItem1
            <<labelItem2<<labelLimit1<<labelLimit2<<labelRange<<labelSpeed;
    labelList1<<labelBias1<<labelEqucct1<<labelFreq1<<labelLevel1<<labelItem11
            <<labelItem22<<labelLimit11<<labelLimit22<<labelRange1<<labelSpeed1;

//    this->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
//    this->setStyleSheet(QString("border:2px solid %1").arg(colorList.at(channel-1)));
//    this->setStyleSheet(QString("border-radius: 9px"));
    this->setStyleSheet(QString("QDialog{background-color:%1;border:2px solid %2;border-radius: 9px;}")
                        .arg(colorList.at(channel-1)).arg(colorList.at(channel-1)));
    for(int i=0;i<labelList.length();i++)
    {
        labelList.at(i)->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
        labelList.at(i)->setFont(QFont("楷体",12));
        labelList1.at(i)->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
        labelList1.at(i)->setFont(QFont("楷体",12));
    }


    labelChannel->setStyleSheet(QString("border:0px solid %1").arg(colorList.at(channel-1)));
    labelChannel->setStyleSheet(QString("border-radius: 0px"));
    labelChannel->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelChannel->setText(tr("通道")+QString::number(channel));
    labelChannel->setFont(QFont("楷体",13));

    labelChannel1->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelClose->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    //labelBias->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel)));
    labelBias1->setText(QString::number(bias)+biasType);
    //labelBias1->setFont(QFont("楷体",12));
    labelEqucct1->setText(equcct);
    labelFreq1->setText(QString::number(frequency)+"Hz");
    labelLevel1->setText(QString::number(level)+levelUnit);
    labelItem11->setText(item1);
    labelItem22->setText(item2);
    labelLimit11->setText(QString::number(item1HiLimit)+"--"+QString::number(item1LowLimit));
    labelLimit22->setText(QString::number(item2HiLimit)+"--"+QString::number(item2LowLimit));
    labelRange1->setText(range);
    labelSpeed1->setText(speed);
}

void clsChannelSettings::onLabelCloseClicked()
{
    emit deleteChannelSettings(channel);
}

void clsChannelSettings::setChannelSettings()
{
    stackedWidget->setCurrentIndex(0);
}

void clsChannelSettings::setChannelRunnings()
{
    stackedWidget->setCurrentIndex(1);
}

void clsChannelSettings::setCloseEnabled(bool bl)
{
    if(bl)
        labelClose->setEnabled(true);
    else
        labelClose->setEnabled(false);
}
