#include "clsUpdateFtdiDataThread.h"
#include "clsFtdiOperation.h"
void clsUpdateFtdiDataThread::run()
{
    this->blStop = false;

    while(!blStop)
    {
        clsConnectSWBox::Ins()->updataFTDIdata();
    }
    clsConnectSWBox::Ins()->stop();
}

void clsUpdateFtdiDataThread::stop()
{
   this->blStop = true;
    clsConnectSWBox::Ins()->stop();
}
