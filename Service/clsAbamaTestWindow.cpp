#include "clsAbamaTestWindow.h"
#include "clsSignalThread.h"
clsAbamaTestWindow::clsAbamaTestWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    connect(sngSignalThread::Ins(),&clsSignalThread::trigCaptured,[=]()
    {
        this->label->setText("Trig Captured");
    });
}
