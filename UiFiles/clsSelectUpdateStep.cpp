#include "clsSelectUpdateStep.h"

clsSelectUpdateStep::clsSelectUpdateStep(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint &~Qt::WindowCloseButtonHint);
}

int clsSelectUpdateStep::selectStep(QWidget *parent, QList<QPoint> steps)
{
   clsSelectUpdateStep *dlg = new clsSelectUpdateStep(parent);

   dlg->cmbSteps->clear();
   for(int i=0; i< steps.length(); i++)
   {
      dlg->cmbSteps->addItem(QString("%1-%2").arg(steps.at(i).x()).arg(steps.at(i).y()));
   }

   dlg->exec();


   return dlg->cmbSteps->currentIndex();


}

void clsSelectUpdateStep::on_btnOk_clicked()
{
    this->accept();
}
