#include "clsSignalProcess.h"
#include "clsTestClass.h"
#include "clsFtdiConnection.h"
clsSignalProcess::clsSignalProcess(QObject *parent) : QObject(parent)
{

}

void clsSignalProcess::setBusy(bool value)
{
    emit busyStatusChanged(value);

    if(value)
        sngControlBox::Ins()->sendCommand(BUSYCMMD, false);
    else
        sngControlBox::Ins()->sendCommand(IDELCMMD, false);
}

void clsSignalProcess::setLcrPassFail(bool value)
{
    emit lcrStatusChanged(value);

    if(value)
        sngControlBox::Ins()->sendCommand(LCRPASSCMMD,false);
    else
        sngControlBox::Ins()->sendCommand(LCRFAILCMMD,false);
}

void clsSignalProcess::setHvPassFail(bool value)
{
    emit hvStatusChanged(value);

    if(value)
        sngControlBox::Ins()->sendCommand(HVPASSCMMD,false);
    else
        sngControlBox::Ins()->sendCommand(HVFAILCMMD,false);


}

void clsSignalProcess::setChannel(int channel)
{
    emit channelChanged(channel);

    sngControlBox::Ins()->sendCommand(QString(SETCHANNEL) + QString::number(i),false);
}

QString clsSignalProcess::getValue()
{
    //For Demo test
    return sngTest::Ins()->getFtdiReadString();
}
