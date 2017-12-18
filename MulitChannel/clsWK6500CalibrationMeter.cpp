#include "clsWK6500CalibrationMeter.h"
#include "clsFtdiOperation.h"
#include "clsLcrConnection.h"
clsWK6500CalibrationMeter::clsWK6500CalibrationMeter()
{

}

void clsWK6500CalibrationMeter::set10KHz()
{
    sngLCRCnnt::Ins()->sendCommand(QString(":METER:FREQ 10000"),false);
}

void clsWK6500CalibrationMeter::setChannel(int value)
{
    clsConnectSWBox::Ins()->setChannel(value);
}

void clsWK6500CalibrationMeter::setUseLoad(bool /*value*/)
{


}

void clsWK6500CalibrationMeter::setConditionForCalibration(int /*noOfTest*/)
{
    //Set Test item 1 Z, item 2 A, Serial, Slow, Range: Auto;
    QStringList gpibCmd;
    QString meter= ":METER:";

    gpibCmd.append(meter+"FUNC:1 "+("Z")+";");  //item1 GPIB
    gpibCmd.append(meter+"FUNC:2 "+("ANGLE")+";");  //Item2 GPIB
    gpibCmd.append(meter+"EQU-CCT "+"SER"+";");

    gpibCmd.append(meter+"FREQ "+QString::number(10E3,'f',6)+";");   //频率
    gpibCmd.append(meter+"RANGE "+"AUTO"+";");
    gpibCmd.append(meter+"SPEED "+"SLOW"+";");

    for(int i=0; i< gpibCmd.length(); i++)
    {
        sngLCRCnnt::Ins()->sendCommand(gpibCmd.at(i), false);
    }
}

QList<double> clsWK6500CalibrationMeter::getOriginZA()
{
    QList<double> results;
    QString res = sngLCRCnnt::Ins()->sendCommand(":METER:TRIG",true);
    res +=",,";

    results.clear();
    QStringList resList = res.split(",");

    results.append(resList.at(0).toDouble());
    results.append(resList.at(1).toDouble());

    return results;
}

void clsWK6500CalibrationMeter::setFreqencyForCal(double value)
{
    this->frequency = value;
    double queryFreq = sngLCRCnnt::Ins()->sendCommand(":METER:FREQ?",true).toDouble();
    if(queryFreq != value)
    {
        sngLCRCnnt::Ins()->sendCommand(":METER:FREQ "+ QString::number(value,'f',6),false);
    }
}

double clsWK6500CalibrationMeter::getFreqency(int /*noOfTest*/)
{
    return frequency;
}
