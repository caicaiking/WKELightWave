#include "clsSelectFtdiChip.h"

clsSelectFtdiChip::clsSelectFtdiChip(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint &~Qt::WindowCloseButtonHint);
}

void clsSelectFtdiChip::setItems(QStringList items)
{
    this->cmbDiscriptor->addItems(items);
}

int clsSelectFtdiChip::selectIndex(const QStringList& items, bool *res,const QString text, QWidget *parent)
{
    clsSelectFtdiChip *dlg = new clsSelectFtdiChip(parent) ;
    dlg->setItems(items);
    dlg->label->setText(text);
    if(dlg->exec() == QDialog::Accepted)
    {
       *res = true;
        return dlg->getSelect();
    }
    else
    {
        *res = false;
        return 99;
    }
}

void clsSelectFtdiChip::on_btnCancel_clicked()
{
    this->reject();
}

void clsSelectFtdiChip::on_btnOk_clicked()
{
    this->accept();
}

int clsSelectFtdiChip::getSelect()
{
    return cmbDiscriptor->currentIndex();
}
