#include <QApplication>
#include "MainDialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    w.show();

    return a.exec();
}
