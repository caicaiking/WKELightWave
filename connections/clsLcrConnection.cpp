#include "clsLcrConnection.h"
#include "QDebug"
#include "clsGlobleVarient.h"
clsLcrConnection::clsLcrConnection(QObject *parent) : QObject(parent)
{
    cnnt =nullptr;
    isInit = false;
}

void clsLcrConnection::setConnectionType(QString cnntType)
{
    this->connectionType = cnntType;
}

void clsLcrConnection::setAddress(QString address)
{
    this->strAddress = address;
}

bool clsLcrConnection::setupConnection()
{
    if(isInit)
        return true;

    cnnt = connectionFactory::getConnection(this->connectionType);
    cnnt->setAddress(this->strAddress);

    this->isInit = cnnt->init();
    if(isInit)
    {
        QString strIdn = cnnt->sendCommand("*IDN?", true);

        QStringList ls = strIdn.split(",");
        if(ls.length()>=2)
        {
            if(!(ls.at(0).contains("WAYNE")|| ls.at(0).contains("KUWAKI")))
            {
                isInit = false;
                return false;
            }
            qDebug()<<"Instrument id " <<ls.at(1);
            if(!ls.at(1).trimmed().isEmpty())
            {
                clsRS::Ins()->instrumentModel=ls.at(1).trimmed();

                QRegExp rx("[PMIA]*([0-9]+)([BPA]?[QL]{0,})");
                if(rx.exactMatch(clsRS::Ins()->instrumentModel))
                {
                    QRegExp rx4100 ("^4[13][0-9]*");
                    if(rx4100.exactMatch(clsRS::Ins()->instrumentModel))
                    {
                        clsRS::Ins()->meterSeries="4300";
                        goto ToHere;
                    }

                    QRegExp rx6500 ("^65[0-9]*[BPA]");
                    if(rx6500.exactMatch(clsRS::Ins()->instrumentModel))
                    {
                        clsRS::Ins()->meterSeries="6500";
                        goto ToHere;
                    }

                    QRegExp rx3260 ("^PMA3260[BA]");
                    if(rx3260.exactMatch(clsRS::Ins()->instrumentModel))
                    {
                        clsRS::Ins()->meterSeries="3260";
                        goto ToHere;
                    }

                    QRegExp rx3255 ("^IA3255[BA][QL]{0,}");
                    if(rx3255.exactMatch(clsRS::Ins()->instrumentModel))
                    {
                        clsRS::Ins()->meterSeries="3255";
                        goto ToHere;
                    }

                    QRegExp rx6440 ("^64[43]0");
                    if(rx6440.exactMatch(clsRS::Ins()->instrumentModel))
                    {
                        clsRS::Ins()->meterSeries="6440";
                        goto ToHere;
                    }


                }
            }
            else
            {
                isInit = false;
                return isInit;
            }
ToHere:
            emit showMessage("LCR设备已连接");
        }
        return isInit;
    }
    return isInit;
}

QString clsLcrConnection::sendCommand(QString command, bool hasReturn)
{
    if(isInit)
        return cnnt->sendCommand(command,hasReturn);
    else
        emit showMessage("LCR设备没有连接");
    qWarning()<<"The LCR connection does't setup conrrectly!";
    return "";

}

void clsLcrConnection::disConnectInstrument()
{
    if(isInit)
        cnnt->disConnect();
}

bool clsLcrConnection::hasInitSucess()
{
    return isInit;
}
