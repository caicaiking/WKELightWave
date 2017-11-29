#include <QApplication>
#include "clsMainTestWindow.h"
#include <qdebug.h>
#include "clsLcrCnntWindow.h"
#include "clsHVCnntWindow.h"
#include "clsFtdiCnntWindow.h"
#include "clsFtdiConnection.h"
#include "clsFtdiOperation.h"
#include "clsUpdateFtdiDataThread.h"
#include "clsAbamaTestWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    sngFtdiCnnt::Ins();
    sngFtdiData::Ins();
    sngFtdiOp::Ins();
    sngRunService::Ins();

    //检查默认IP是否能连接到仪器，如果不能弹出连接对话框
    if(clsLcrCnntWindow::setupConnection()!= true)
    {
        clsLcrCnntWindow window;
        window.exec();
    }

    //检查默认的地址能否连接到高压仪器，如果不能弹出连接对话框
    if(clsHVCnntWindow::setupConnection()!= true)
    {
        clsHVCnntWindow window;
        window.exec();
    }

    //检查是否连接到WKE control Box，如果不能弹出连接设置对话框
    if(clsFtdiCnntWindow::setupConnection() != true)
    {
        clsFtdiCnntWindow window;
        window.exec();
    }

    //如果初始化完成的话，Binning初始化。
    if(sngFtdiCnnt::Ins()->hasInitSucess())
    {
        sngFtdiOp::Ins()->setBusy(false);
        sngFtdiOp::Ins()->setLcrPassFail(false);
        sngFtdiOp::Ins()->setHvPassFail(false);
        sngFtdiOp::Ins()->setChannel(0);
        sngFtdiOp::Ins()->setReadString("00000000");
    }

    clsMainTestWindow window;
    window.show();

    return a.exec();
}
