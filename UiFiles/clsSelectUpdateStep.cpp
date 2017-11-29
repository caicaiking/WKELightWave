#include "clsSelectUpdateStep.h"

clsSelectUpdateStep::clsSelectUpdateStep(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint &~Qt::WindowCloseButtonHint);
}

int clsSelectUpdateStep::selectStep(QWidget *parent, QList<int> steps)
{
   clsSelectUpdateStep *dlg = new clsSelectUpdateStep(parent);

   dlg->cmbSteps->clear();
   for(int i=0; i< steps.length(); i++)
   {
      dlg->cmbSteps->addItem(QString::number(steps.at(i)+1));
   }

   dlg->exec();
   return (dlg->cmbSteps->currentText().toInt()-1);

}

void clsSelectUpdateStep::on_btnOk_clicked()
{
    this->accept();
}
