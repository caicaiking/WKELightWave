#include "clsHVChannelSettings.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "publicUtility.h"
#include "doubleType.h"
#include "doubleType.h"
#include "publicUtility.h"
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
                this->hiLimit = conditionMap["hiLimit"].toDouble();
                this->lowLimit = conditionMap["lowLimit"].toDouble();
                this->voltage = conditionMap["voltage"].toDouble();
                this->relaySwitch = conditionMap["relaySwitch"].toString();
                this->hvStatus = conditionMap["volSwitch"].toString();

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

    int colorIndex =(channel-1) % colorList.length();
    this->setStyleSheet(QString("QDialog{background-color:%1;border:2px solid %2;border-radius: 9px;}")
                        .arg(colorList.at(colorIndex)).arg(colorList.at(colorIndex)));

    //    labelChannel->setStyleSheet(QString("border:0px solid %1").arg(colorList.at(channel-1)));
    //    labelChannel->setStyleSheet(QString("border-radius: 0px"));
    labelChannel->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelChannel->setText(tr("通道")+QString::number(channel));
    labelChannel->setFont(QFont("楷体",17));

    labelChannel1->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    // labelClose->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelItem->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelItem->setFont(QFont("楷体",17));
    labelItem11->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelItem11->setText("R");
    labelItem11->setFont(QFont("楷体",18));

    labelLimit1->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelLimit1->setFont(QFont("楷体",13));
    labelLimit11->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelLimit11->setFont(QFont("楷体",13));

    labelResItem1->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelResItem1->setFont(QFont("楷体",13));
    labelRes1->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelRes1->setFont(QFont("楷体",13));

    labelResStatus1->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelResStatus1->setFont(QFont("楷体",13));

    labelRelay->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelRelay->setFont(QFont("楷体",13));
    labelRelayRes->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelRelayRes->setFont(QFont("楷体",13));

    labelVoltage->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelVoltage->setFont(QFont("楷体",13));
    labelVoltageRes->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelVoltageRes->setFont(QFont("楷体",13));


    doubleType dt;
    dt.setData(hiLimit);

    QString strHiLimit = dt.formateToString(6) + publicUtility::getSuffix("R");
    dt.setData(lowLimit);
    QString strLowLimit = dt.formateToString(6) + publicUtility::getSuffix("R");
    this->labelLimit11->setText(strLowLimit + "--" + strHiLimit);

    dt.setData(this->voltage);
    this->labelVoltageRes->setText(dt.formateToString(6) + "V");

    labelRelayRes->setText(relaySwitch);

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
    bool resBl;
    double tmpRes;
    QString resUnit;
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(res.toUtf8(), &error);

    if(error.error != QJsonParseError::NoError)
        return;

    if(jsonDocument.isEmpty() || jsonDocument.isNull())
        return;

    conditionMap = jsonDocument.toVariant().toMap();

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

void clsHVChannelSettings::setStep(int i)
{
    labelChannel1->setText("s"+QString::number(i+1));
    intStep =i;
}

int clsHVChannelSettings::getStep() const
{
    return intStep;
}

void clsHVChannelSettings::onCloseLabelClicked()
{
    emit deleteChannelSettings(intStep);
}
