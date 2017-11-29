#include "clsWarningBox.h"
#include <QMessageBox>

clsWarningBox::clsWarningBox(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint &~Qt::WindowCloseButtonHint);

    this->selected = QMessageBox::No;
}

int clsWarningBox::warning(QWidget* parent, QString title, QString info)
{
    clsWarningBox * dlg = new clsWarningBox(parent);
    dlg->setWindowTitle(title);
    dlg->lblMessage->setText(info);

    dlg->exec();

    return dlg->getSelected();

}

int clsWarningBox::getSelected() const
{
    return selected;
}

void clsWarningBox::on_btnUpdate_clicked()
{
    this->selected = QMessageBox::Ok;
    this->accept();
}

void clsWarningBox::on_btnNewStep_clicked()
{
    this->selected = QMessageBox::Yes;
    this->accept();
}

void clsWarningBox::on_btnCancel_clicked()
{
    this->selected = QMessageBox::No;
    this->accept();
}
