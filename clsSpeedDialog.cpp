#include "clsSpeedDialog.h"

clsSpeedDialog::clsSpeedDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
}

QString clsSpeedDialog::getSpeed()
{
    return this->speed;
}

void clsSpeedDialog::on_btnMax_clicked()
{
    this->speed="MAX";
    this->accept();
}

void clsSpeedDialog::on_btnFast_clicked()
{
    this->speed="FAST";
    this->accept();
}

void clsSpeedDialog::on_btnMed_clicked()
{
    this->speed="MED";
    this->accept();
}

void clsSpeedDialog::on_btnSlow_clicked()
{
    this->speed="SLOW";
    this->accept();
}

//void clsSpeedDialog::on_btnClose_clicked()
//{
//    this->close();
//}
