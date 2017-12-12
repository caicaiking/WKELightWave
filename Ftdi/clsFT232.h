#ifndef CLSFT232_H
#define CLSFT232_H

#include <QObject>
#include <windows.h>
#include "FTD2XX.H"
#include <QStringList>
#include <QTimer>
class clsFT232: public QObject
{
    Q_OBJECT
public:
    explicit clsFT232(QObject *parent=0);

    QStringList getOutputs() const;

    QString sendCommand(QString cmmd, bool hasReturn= false);

    void setInstrument(const QString &value);
private slots:
    QString readSettings();
    void writeSettings(QString sn);

    void timerProc();
private:
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    DWORD numDevs;
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    QStringList deviceInfo;
    QStringList outputs;

    QString instrument;
    bool isInit;

    bool forceQuit;
    QTimer *timer;
public slots:
    bool getDeviceList();
    bool initConnection();
    bool closeDevice();

};

#endif // CLSFT232_H
