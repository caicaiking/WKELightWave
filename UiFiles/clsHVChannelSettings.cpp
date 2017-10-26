#include "clsHVChannelSettings.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "publicUtility.h"
#include "doubleType.h"

clsHVChannelSettings::clsHVChannelSettings(clsMeter *parent) :
    clsMeter(parent)
{
    setupUi(this);

    connect(labelClose,SIGNAL(labelClicked()),this,SLOT(onCloseLabelClicked()));
}

void clsHVChannelSettings::setCondition(const QString condition)
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
                this->item=conditionMap["item"].toString();
                this->resStatus=conditionMap["resStatus"].toString();
                this->res=conditionMap["res"].toDouble();
                this->channel=conditionMap["channel"].toInt();
            }
        }
    }
}

void clsHVChannelSettings::setChannel(const int channel)
{
    this->channel=channel;
}

void clsHVChannelSettings::updateLabels()
{
    QStringList colorList;
    colorList<<"#D891EF"<<"#FFBF00"<<"#00FFFF"<<"#FDEE00"<<"#D0FF14"<<"#D19FE8"
            <<"#FA6E79"<<"#FE6F5E"<<"#ACE5EE"<<"#66FF00"<<"#FF007F"<<"#84DE02"<<"#1F75FE"
           <<"#08E8DE"<<"#FFAA1D"<<"#FF55A3"<<"#FF033E"<<"#FF2052"<<"#E0218A"<<"#ACE5EE";

    this->setStyleSheet(QString("QDialog{background-color:%1;border:2px solid %2;border-radius: 9px;}")
                        .arg(colorList.at(channel-1)).arg(colorList.at(channel-1)));

//    labelChannel->setStyleSheet(QString("border:0px solid %1").arg(colorList.at(channel-1)));
//    labelChannel->setStyleSheet(QString("border-radius: 0px"));
    labelChannel->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelChannel->setText(tr("通道")+QString::number(channel));
    labelChannel->setFont(QFont("楷体",17));

    labelChannel1->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelClose->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelItem->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelItem->setFont(QFont("楷体",17));
    labelItem11->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelItem11->setText("R");
    labelItem11->setFont(QFont("楷体",18));

    labelLimit1->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelLimit1->setFont(QFont("楷体",13));
    labelLimit11->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelLimit11->setFont(QFont("楷体",13));

    labelResItem1->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelResItem1->setFont(QFont("楷体",13));
    labelRes1->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelRes1->setFont(QFont("楷体",13));

    labelResStatus1->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelResStatus1->setFont(QFont("楷体",13));

    labelRelay->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelRelay->setFont(QFont("楷体",13));
    labelRelayRes->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelRelayRes->setFont(QFont("楷体",13));

    labelVoltage->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelVoltage->setFont(QFont("楷体",13));
    labelVoltageRes->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelVoltageRes->setFont(QFont("楷体",13));
}

void clsHVChannelSettings::setChannelSettings()
{
    stackedWidget->setCurrentIndex(0);
}

void clsHVChannelSettings::setChannelRunnings()
{
    stackedWidget->setCurrentIndex(1);
}

void clsHVChannelSettings::setCloseEnabled(const bool bl)
{
    if(bl)
        labelClose->setEnabled(true);
    else
        labelClose->setEnabled(false);
}

void clsHVChannelSettings::updateRes(const QString res)
{
    QVariantMap conditionMap;
    conditionMap=publicUtility::parseConditions(res);
    bool resBl;
    double tmpRes;
    QString resUnit;
    tmpRes=conditionMap["result"].toDouble();
    resBl=conditionMap["resStatus"].toBool();
    resUnit=conditionMap["resUnit"].toString();
    if(resBl)
    {
        labelResItem1->setStyleSheet(QString("background-color:#66FF00"));
        labelRes1->setStyleSheet(QString("background-color:#66FF00"));
        labelResStatus1->setStyleSheet(QString("background-color:#66FF00"));
        labelResStatus1->setText(tr("PASS"));
    }
    else
    {
        labelResItem1->setStyleSheet(QString("background-color:red"));
        labelRes1->setStyleSheet(QString("background-color:red"));
        labelResStatus1->setStyleSheet(QString("background-color:red"));
        labelResStatus1->setText(tr("FAIL"));
    }
    doubleType dt;
    dt.setData(tmpRes,"");
    labelRes1->setText(dt.formateToString(6)+resStatus);
}

void clsHVChannelSettings::onCloseLabelClicked()
{
    emit deleteChannelSettings(channel);
}
