#include "clsHightVoltage.h"
#include "NumberInput.h"

clsHightVoltage::clsHightVoltage(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->volSwitch=tr("开");
    this->voltage=25.0;
}

QString clsHightVoltage::getVoltageSwitch() const
{
    return this->volSwitch;
}

double clsHightVoltage::getVoltage() const
{
    return this->voltage;
}

void clsHightVoltage::updateCommand()
{

}

void clsHightVoltage::on_btnSwitch_clicked()
{
    if(btnSwitch->text()==tr("开"))
    {
        this->volSwitch=tr("关");
        btnSwitch->setText(tr("关"));
    }
    else if(btnSwitch->text()==tr("关"))
    {
        this->volSwitch=tr("开");
        btnSwitch->setText(tr("开"));
    }
}

void clsHightVoltage::on_btnVoltage_clicked()
{
    NumberInput *dlg=new NumberInput(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        voltage=dlg->getNumber();
        btnVoltage->setText(QString::number(voltage)+"V");
    }
}

void clsHightVoltage::on_btnOK_clicked()
{
    //updateCommand();
    this->accept();
}

void clsHightVoltage::on_btnCancel_clicked()
{
    this->reject();
}
