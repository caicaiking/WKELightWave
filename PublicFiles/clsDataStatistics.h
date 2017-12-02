#ifndef CLSDATASTATISTICS_H
#define CLSDATASTATISTICS_H

#include <QObject>
#include <QTime>
#include <QTimer>

class clsDataStatistics: public QObject
{
    Q_OBJECT
public:
   explicit clsDataStatistics(QObject *parent);
   void addData(bool value);
signals:
   void showTotle(QString);
   void showPass(QString);
   void showFail(QString);
   void showSpeed(QString);
   void showPassRate(QString);

private slots:
   void showInfo();
private:
    int totle, pass, fail;
    QTime t1,t2;
    int trigMs;
    QTimer *timer;
};

#endif // CLSDATASTATISTICS_H
