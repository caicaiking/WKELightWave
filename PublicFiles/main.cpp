#include <QApplication>
#include "MainDialog.h"
#include "clsSignalThread.h"
#include <qdebug.h>
#include <QObject>
#include "clsAbamaTestWindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    sngSignalThread::Instance()->start();

    //clsAbamaTestWindow abT;
    //abT.exec();


    MainDialog w;
    w.show();

    //当关闭了主窗口就停止接收Trig信号
    QObject::connect(&w,&MainDialog::close, sngSignalThread::Instance(),&clsSignalThread::stop);

    return a.exec();
}
