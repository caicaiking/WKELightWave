#include "clsChannelSettings.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "publicUtility.h"
#include "doubleType.h"
#include <QDebug>

clsChannelSettings::clsChannelSettings(clsMeter *parent) :
    clsMeter(parent)
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
                this->suffix1=conditionMap["suffix1"].toString();
                this->suffix2=conditionMap["suffix2"].toString();
                this->relaySwitch=conditionMap["relaySwitch"].toString();

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
    labelChannel->setFont(QFont("楷体",17));

    labelChannel1->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelClose->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelRelay->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelRelaySwitch->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelBias1->setText(QString::number(bias)+biasType+","+biasSwitch);
    //labelBias1->setFont(QFont("楷体",12));
    labelEqucct1->setText(equcct);
    doubleType dt;
    dt.setData(frequency,"");
    labelFreq1->setText(dt.formateToString(6)+"Hz");

    dt.setData(level,"");
    labelLevel1->setText(dt.formateToString(6)+levelUnit);

    labelItem11->setText(item1);
    labelItem22->setText(item2);

    QString sf1=suffix1.remove(0,1);
    dt.setData(item1HiLimit,"");
    QString hiLimit=dt.formateToString(6)+sf1;
    dt.setData(item1LowLimit,"");
    QString lowLimit=dt.formateToString(6)+sf1;
    labelLimit11->setText(lowLimit+"--"+hiLimit);

    QString sf2=suffix2.remove(0,1);
    dt.setData(item2HiLimit,"");
    QString hiLimit2=dt.formateToString(6)+sf2;
    dt.setData(item2LowLimit,"");
    QString lowLimit2=dt.formateToString(6)+sf2;
    labelLimit22->setText(lowLimit2+"--"+hiLimit2);

    labelRange1->setText(range);
    labelSpeed1->setText(speed);
    labelRelaySwitch->setText(relaySwitch);
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

void clsChannelSettings::updateRes(const QString res)
{
    QVariantMap resMap;
    resMap=publicUtility::parseConditions(res);
    bool resStatus1,resStatus2;
    double result1,result2;
    QString resUnit1,resUnit2;
    resStatus1=resMap["resStatus1"].toBool();
    resStatus2=resMap["resStatus2"].toBool();
    result1=resMap["result1"].toDouble();
    result2=resMap["result2"].toDouble();
    resUnit1=resMap["resUnit1"].toString();
    resUnit2=resMap["resUnit2"].toString();
    if(resStatus1)
    {
        labelResStatus1->setStyleSheet(QString("background-color:#66FF00"));
        labelItem1->setStyleSheet(QString("background-color:#66FF00"));
        labelRes1->setStyleSheet(QString("background-color:#66FF00"));
        labelResStatus1->setText(tr("PASS"));
    }
    else
    {
        labelResStatus1->setStyleSheet(QString("background-color:red"));
        labelItem1->setStyleSheet(QString("background-color:red"));
        labelRes1->setStyleSheet(QString("background-color:red"));
        labelResStatus1->setText(tr("FAIL"));
    }
    if(resStatus2)
    {
        labelResStatus2->setStyleSheet(QString("background-color:#66FF00"));
        labelItem2->setStyleSheet(QString("background-color:#66FF00"));
        labelRes2->setStyleSheet(QString("background-color:#66FF00"));
        labelResStatus2->setText(tr("PASS"));
    }
    else
    {
        labelResStatus2->setStyleSheet(QString("background-color:red"));
        labelItem2->setStyleSheet(QString("background-color:red"));
        labelRes2->setStyleSheet(QString("background-color:red"));
        labelResStatus2->setText(tr("FAIL"));
    }
    doubleType dt;
    dt.setData(result1,"");
    labelRes1->setText(dt.formateToString(6)+resUnit1);
    dt.setData(result2,"");
    labelRes2->setText(dt.formateToString(6)+resUnit2);
}
