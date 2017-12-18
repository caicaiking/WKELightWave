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
    void insertRecord(double freq, int channal, double z, double a, QString type);
    void updataText();
    void saveSettings();
private slots:

    void on_btnRCLoadCalibration_clicked();
    void on_btnDone_clicked();
    void on_btnMultiFreq_clicked();
    void on_btnCancel_clicked();
    void  on_btnOpenTrim_clicked();
    void on_btnShortTrim_clicked();
private:
    double ocZ,ocA,scZ,scA,loadZ,loadA, stdA,stdZ;
    double freq;
    QList<double> freqList;
    clsInstrumentCalibration *meter;
    QStringList channels;
    QMap<int, QList<double> > calFreq;
    QList<double> getCalDataFromDb(double freq, int channal, QString type);
    void getAllDataFromDb(double freq, int channel);
    QList<double> getCalFrequencys();
    QList<int> getCalChannels();
    int showCalMessage(QString calType, double calFreq, int channel);
    int showCalMessage(QString calType, int channel);
    void setCalLabelInfo(QLabel *lbl, QString calType);
    void readSettings();
    QList<clsTestConditons *> steps;
    double getFreqFromConditon(const QString condition);
};

#endif // CLSCALIBRATION_H
