#include "clsSpeedDialog.h"

clsSpeedDialog::clsSpeedDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
}

QString clsSpeedDialog::getSpeed()
{
    return this->speed;
}

void clsSpeedDialog::on_btnMax_clicked()
{
    this->speed=tr("最快");
    this->accept();
}

void clsSpeedDialog::on_btnFast_clicked()
{
    this->speed=tr("快速");
    this->accept();
}

void clsSpeedDialog::on_btnMed_clicked()
{
    this->speed=tr("中速");
    this->accept();
}

void clsSpeedDialog::on_btnSlow_clicked()
{
    this->speed=tr("慢速");
    this->accept();
}

//void clsSpeedDialog::on_btnClose_clicked()
//{
//    this->close();
//}
