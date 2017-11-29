#include "clsUpdateFtdiDataThread.h"
#include "clsFtdiOperation.h"
void clsUpdateFtdiDataThread::run()
{
    this->blStop = false;

    while(!blStop)
    {
        sngFtdiOp::Ins()->updataFTDIdata();
    }
    sngFtdiOp::Ins()->stop();
}

void clsUpdateFtdiDataThread::stop()
{
   this->blStop = true;
    sngFtdiOp::Ins()->stop();
}
