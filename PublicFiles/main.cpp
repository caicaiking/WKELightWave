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
#include <QSplashScreen>
#include <QPixmap>
#include "publicUtility.h"
#include "logmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //设置Splash 屏幕
    QPixmap pixmap(":/splashScreen2.png");
    QSplashScreen splash(pixmap);

    splash.show();
    splash.setFont(QFont("楷体",12, QFont::Normal));
    splash.showMessage(QObject::tr("版本号：%1 正在初始化测试窗口，请稍等...").arg(publicUtility::getVersion()),Qt::AlignBottom |Qt::AlignRight,Qt::red);
    splash.show();
    publicUtility::sleepMs(2000);

    a.processEvents();

    sngFtdiCnnt::Ins();
    clsConnectSWBox::Ins();
    sngRunService::Ins();

    //检查默认IP是否能连接到仪器，如果不能弹出连接对话框
    splash.showMessage(QObject::tr("初始化WK6500B网络连接..."),Qt::AlignBottom |Qt::AlignRight,Qt::red);
    publicUtility::sleepMs(500);
    if(clsLcrCnntWindow::setupConnection()!= true)
    {
        clsLcrCnntWindow window;
        window.exec();
    }

    //检查默认的地址能否连接到高压仪器，如果不能弹出连接对话框
    splash.showMessage(QObject::tr("初始化高压机串口连接..."),Qt::AlignBottom |Qt::AlignRight,Qt::red);
    publicUtility::sleepMs(500);
    if(clsHVCnntWindow::setupConnection()!= true)
    {
        clsHVCnntWindow window;
        window.exec();
    }

    //检查是否连接到WKE control Box，如果不能弹出连接设置对话框
    splash.showMessage(QObject::tr("初始化WKE控制箱FTDI连接..."),Qt::AlignBottom |Qt::AlignRight,Qt::red);
    publicUtility::sleepMs(500);
    if(clsFtdiCnntWindow::setupConnection() != true)
    {
        clsFtdiCnntWindow window;
        window.exec();
    }

    //如果初始化完成的话，Binning初始化。
    if(sngFtdiCnnt::Ins()->hasInitSucess())
    {
        clsConnectSWBox::Ins()->setBusy(false);
        clsConnectSWBox::Ins()->setLcrPassFail(false);
        clsConnectSWBox::Ins()->setHvPassFail(false);
        clsConnectSWBox::Ins()->setChannel(0);
        clsConnectSWBox::Ins()->setReadString("00000000");
    }

    //开始更新串口数据
    sngFtdiData::Ins();

    clsMainTestWindow window;
    splash.finish(&window);
    window.show();

    return a.exec();
}
