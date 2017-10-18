#include "clsAbamaTestWindow.h"
#include "clsSignalThread.h"
clsAbamaTestWindow::clsAbamaTestWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    connect(sngSignalThread::Instance(),&clsSignalThread::trigCaptured,[=]()
    {
        this->label->setText("Trig Captured");
    });
}
