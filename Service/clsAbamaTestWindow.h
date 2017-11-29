#ifndef CLSABAMATESTWINDOW_H
#define CLSABAMATESTWINDOW_H

#include "ui_clsAbamaTestWindow.h"
#include <QCloseEvent>

#include "clsRunningThread.h"

class clsAbamaTestWindow : public QDialog, private Ui::clsAbamaTestWindow
{
    Q_OBJECT
public:
    explicit clsAbamaTestWindow(QWidget *parent = 0);
protected:
   void closeEvent(QCloseEvent *event);
private slots:
   void on_btnTrig0_clicked();
   void on_btnTrig1_clicked();
   void on_btnReset0_clicked();
   void on_btnReset1_clicked();


   void setLabelColor(QLabel * lbl);
   void setTrigLabel();
   void setResetLabel();
   void on_btnSetBusy_toggled(bool checked);

   void on_btnSetLcr_toggled(bool checked);

   void on_btnSetHv_toggled(bool checked);

   void setLcrStatus(bool status);
   void setHVStatus(bool status);
   void setBusyStatus(bool status);


private:
   clsRunningThread *trigThread, *resetThread;
private:
};

#endif // CLSABAMATESTWINDOW_H
