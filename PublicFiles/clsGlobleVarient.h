#ifndef CLSGLOBLEVARIENT_H
#define CLSGLOBLEVARIENT_H
#include <QString>
#include "singleton.h"
class clsGlobleVarient
{
public:
    clsGlobleVarient();

    QString meterSeries;
    QString instrumentModel;
};

typedef Singleton<clsGlobleVarient> clsRS;
#endif // CLSGLOBLEVARIENT_H
