#ifndef CLSINSTRUMENT_H
#define CLSINSTRUMENT_H

#include <QObject>

class clsInstrument : public QObject
{
    Q_OBJECT
public:
    explicit clsInstrument(QObject *parent = nullptr);

    virtual void setConditions(QString)=0;
    virtual void updateGpib()=0;
    virtual int getItemCount()=0;
    virtual double getRes(int )=0;
    virtual bool getResStatus(int i)=0;
    virtual bool getTotleStatusl()=0;

signals:

public slots:
};

#endif // CLSINSTRUMENT_H
