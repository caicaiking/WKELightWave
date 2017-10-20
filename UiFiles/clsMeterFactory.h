#ifndef CLSMETERFACTORY_H
#define CLSMETERFACTORY_H

#include "clsMeter.h"
#include "clsChannelSettings.h"
#include "clsHVChannelSettings.h"


class clsMeterFactory
{
public:
    clsMeterFactory();

    static clsMeter* getMeter(QString m);

};

#endif // CLSMETERFACTORY_H
