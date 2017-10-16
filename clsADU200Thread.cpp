#include "clsADU200Thread.h"

clsADU200Thread::clsADU200Thread(QObject *parent) : QThread(parent)
{
    adu200=new clsADU200();
    isInit=adu200->initADU200();
}

void clsADU200Thread::run()
{
    while(isInit)
    {
        if(adu200->getInputSignal(0))
        {
            emit adu200Trig();
            sleep(0.01);
        }
    }
}

void clsADU200Thread::setPass()
{
    adu200->setPass();
}

void clsADU200Thread::setFail()
{
    adu200->setFail();
}

void clsADU200Thread::setBDA()
{
    adu200->setBDA();
}

void clsADU200Thread::resetBDA()
{
    adu200->resetBDA();
}
