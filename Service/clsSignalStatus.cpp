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

void clsSignalStatus::setStatus(QString meter, bool value)
{
   if(meter == "WK6500")
       setLCRStatus(value);
   else if(meter == "HV")
       setHVStatus(value);
   else
   {
       //Do nothing here.
       //The program can not run to here.
   }
}

void clsSignalStatus::setLCRStatus(bool value)
{
    lcrStatus &= value;
}

void clsSignalStatus::setHVStatus(bool value)
{
   hvStatus &=value;
}
