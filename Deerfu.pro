#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T09:34:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Deerfu
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += PublicFiles UiFiles Service

DESTDIR =$$PWD/Libs/
LIBS += $$PWD/Libs/AduHid.lib \
        $$PWD/Libs/AduHid.dll

RESOURCES += \
    images/res.qrc

HEADERS += \
    PublicFiles/clsMeterLimit.h \
    PublicFiles/doubleType.h \
    UiFiles/clsChannelSettings.h \
    UiFiles/clsHightVoltage.h \
    UiFiles/clsLabel.h \
    UiFiles/clsNewSetup.h \
    UiFiles/clsRangeDialog.h \
    UiFiles/clsRunningStatus.h \
    UiFiles/clsSpeedDialog.h \
    UiFiles/clsWK6500Items.h \
    UiFiles/clsWK6500Meter.h \
    UiFiles/clsWKEControlBox.h \
    UiFiles/frmSetLimit.h \
    UiFiles/MainDialog.h \
    UiFiles/NumberInput.h \
    Service/clsRunService.h \
    Service/singleton.h \
    Service/clsInstrument.h \
    Service/clsSignalStatus.h \
    Service/clsSignalThread.h \
    Service/clsControlBox.h \
    Service/AduHid.h

SOURCES += \
    PublicFiles/clsMeterLimit.cpp \
    PublicFiles/doubleType.cpp \
    PublicFiles/main.cpp \
    UiFiles/clsChannelSettings.cpp \
    UiFiles/clsHightVoltage.cpp \
    UiFiles/clsLabel.cpp \
    UiFiles/clsNewSetup.cpp \
    UiFiles/clsRangeDialog.cpp \
    UiFiles/clsRunningStatus.cpp \
    UiFiles/clsSpeedDialog.cpp \
    UiFiles/clsWK6500Items.cpp \
    UiFiles/clsWK6500Meter.cpp \
    UiFiles/clsWKEControlBox.cpp \
    UiFiles/frmSetLimit.cpp \
    UiFiles/MainDialog.cpp \
    UiFiles/NumberInput.cpp \
    Service/clsRunService.cpp \
    Service/clsInstrument.cpp \
    Service/clsSignalStatus.cpp \
    Service/clsSignalThread.cpp \
    Service/clsControlBox.cpp

FORMS += \
    UiFiles/clsChannelSettings.ui \
    UiFiles/clsHightVoltage.ui \
    UiFiles/clsIODialog.ui \
    UiFiles/clsNewSetup.ui \
    UiFiles/clsRangeDialog.ui \
    UiFiles/clsRunningStatus.ui \
    UiFiles/clsSpeedDialog.ui \
    UiFiles/clsWK6500Items.ui \
    UiFiles/clsWK6500Meter.ui \
    UiFiles/clsWKEControlBox.ui \
    UiFiles/frmSetLimit.ui \
    UiFiles/MainDialog.ui \
    UiFiles/NumberInput.ui


