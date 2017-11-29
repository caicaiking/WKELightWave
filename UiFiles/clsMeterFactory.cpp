#include "clsMeterFactory.h"

clsMeterFactory::clsMeterFactory()
{

}

clsMeter *clsMeterFactory::getMeter(QString m)
{
    if(m=="WK6500")
        return new clsChannelSettings;
    else if(m=="HV")
        return new clsHVChannelSettings;
}
