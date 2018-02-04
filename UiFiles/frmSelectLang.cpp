#include "frmSelectLang.h"

frmSelectLang::frmSelectLang(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint &~Qt::WindowCloseButtonHint);
}

int frmSelectLang::getLanguage(QWidget *parent)
{

    frmSelectLang * dlg = new frmSelectLang(parent);
    if(dlg->exec() == QDialog::Accepted)
    {
       return dlg->getChoice();
    }
}

void frmSelectLang::on_btnOk_clicked()
{
    if(rbEnglish->isChecked())
        this->choice = 2;
    else
        this->choice = 1;

    this->accept();
}

