#ifndef CLSCALIBRATION_H
#define CLSCALIBRATION_H

#include "ui_clsCalibration.h"
#include "clsDataProcess.h"
#include "clsInstrumentCalibration.h"
#include "clsTestConditon.h"
#include <QMap>
class clsCalibration : public QDialog, private Ui::clsCalibration
{
    Q_OBJECT

public:
    explicit clsCalibration(QWidget *parent = 0);
    void setMeter(clsInstrumentCalibration *meter);
    void setSteps(const QList<clsTestConditons *> steps);
    void insertRecord(double freq, QPoint channal, double z, double a, QString type);
    void updataText();
    void saveSettings();

    struct Parameters
    {
        double freqnecy;
        bool switchStatus;
        QPoint channel;
        bool isUsable;
    };

private slots:

    void on_btnDone_clicked();
    void on_btnMultiFreq_clicked();
    void  on_btnOpenTrim_clicked();
    void on_btnShortTrim_clicked();
    void on_btnClearCalData_clicked();

    void on_btnGoldenCalibrate_clicked();

private:
    double ocZ,ocA,scZ,scA,loadZ,loadA, stdA,stdZ;
    double freq;
    QList<double> freqList;
    clsInstrumentCalibration *meter;
    QList<Parameters> channels;
    QList<double> getCalDataFromDb(double freq, QPoint channal, QString type);
    void getAllDataFromDb(double freq, int channel);
    int showCalMessage(QString calType, double calFreq, QPoint channel);
    int showCalMessage(QString calType, QPoint channel);
    void setCalLabelInfo(QLabel *lbl, QString calType);
    void readSettings();
    QList<clsTestConditons *> steps;
    Parameters getParametersFromConditon(const QString condition);
    QString ps(QPoint p);
    bool getSwitchStatusFromCondition(const QString condition);
};

#endif // CLSCALIBRATION_H
