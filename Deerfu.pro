#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T09:34:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Deerfu
TEMPLATE = app

LIBS +=AduHid.lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    clsWK6500Meter.cpp \
    clsRangeDialog.cpp \
    clsSpeedDialog.cpp \
    clsWK6500Items.cpp \
    doubleType.cpp \
    NumberInput.cpp \
    clsADU200.cpp \
    clsADU200Thread.cpp \
    clsWKEControlBox.cpp \
    clsLabel.cpp \
    clsHightVoltage.cpp \
    MainDialog.cpp \
    clsNewSetup.cpp \
    clsChannelSettings.cpp \
    frmSetLimit.cpp \
    UserfulFunctions.cpp \
    clsMeterLimit.cpp \
    clsRunningStatus.cpp

HEADERS += \
    clsWK6500Meter.h \
    clsRangeDialog.h \
    clsSpeedDialog.h \
    clsWK6500Items.h \
    doubleType.h \
    NumberInput.h \
    AduHid.h \
    clsADU200.h \
    clsADU200Thread.h \
    clsWKEControlBox.h \
    clsLabel.h \
    clsHightVoltage.h \
    MainDialog.h \
    clsNewSetup.h \
    clsChannelSettings.h \
    frmSetLimit.h \
    UserfulFunctions.h \
    clsMeterLimit.h \
    Globle.h \
    clsRunningStatus.h

FORMS += \
    clsWK6500Meter.ui \
    clsRangeDialog.ui \
    clsSpeedDialog.ui \
    clsWK6500Items.ui \
    NumberInput.ui \
    clsIODialog.ui \
    clsWKEControlBox.ui \
    clsHightVoltage.ui \
    MainDialog.ui \
    clsNewSetup.ui \
    clsChannelSettings.ui \
    frmSetLimit.ui \
    clsRunningStatus.ui

RESOURCES += \
    images/res.qrc
