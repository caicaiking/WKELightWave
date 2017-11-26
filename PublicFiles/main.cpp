#include <QApplication>
#include "MainDialog.h"
#include "clsSignalThread.h"
#include <qdebug.h>
#include <QObject>
#include "clsLcrCnntWindow.h"
#include "clsHVCnntWindow.h"
#include "clsFtdiCnntWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    sngSignalThread::Ins()->start();

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

    MainDialog w;
    w.show();

    //当关闭了主窗口就停止接收Trig信号
    QObject::connect(&w,&MainDialog::close, sngSignalThread::Ins(),&clsSignalThread::stop);

    return a.exec();
}
