#include "clsSignalStatus.h"

clsSignalStatus::clsSignalStatus(QObject *parent) : QObject(parent)
{
   lcrStatus = true;
   hvStatus = true;
}

void clsSignalStatus::resetLCRStatus()
{
   lcrStatus = true;
}

void clsSignalStatus::resetHVStatus()
{
   hvStatus = true;
}

bool clsSignalStatus::getLcrStatus() const
{
    return lcrStatus;
}

bool clsSignalStatus::getHvStatus() const
{
    return hvStatus;
}

void clsSignalStatus::setLCRStatus(bool value)
{
    lcrStatus &= value;
}

void clsSignalStatus::setHVStatus(bool value)
{
   hvStatus &=value;
}
