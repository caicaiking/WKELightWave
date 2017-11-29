#ifndef CLSRUNNINGMETERFACTORY_H
#define CLSRUNNINGMETERFACTORY_H
#include "clsInstrument.h"
#include "clsHVRunningMode.h"
#include "clsWK6500RunningMode.h"

class clsRunningMeterFactory
{
public:
    static clsInstrument *getMeter(QString meter)
    {
        if(meter =="WK6500")
            return sngWK6500Run::Ins();
        else if(meter == "HV")
            return sngHVRun::Ins();
        else
            return (clsInstrument *)0;

    }
};

#endif // CLSRUNNINGMETERFACTORY_H
