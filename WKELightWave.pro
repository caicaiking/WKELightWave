#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T09:34:49
#
#-------------------------------------------------

QT       += core gui network serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WKELightWave
TEMPLATE = app

#当发布产品的时候一定要将此行注释去掉
DEFINES += USE_MULTI_CHANNEL

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += PublicFiles UiFiles Service Instruments connections Ftdi MulitChannel Qextseial update


DESTDIR =$$PWD/Libs/

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
    UiFiles/clsSpeedDialog.h \
    UiFiles/clsWK6500Items.h \
    UiFiles/clsWK6500Meter.h \
    UiFiles/frmSetLimit.h \
    UiFiles/NumberInput.h \
    PublicFiles/publicUtility.h \
    UiFiles/clsHVChannelSettings.h \
    UiFiles/clsMeterFactory.h \
    UiFiles/clsMeter.h \
    Service/clsSignalStatus.h \
    Service/singleton.h \
    Service/clsRunService.h \
    Instruments/clsInstrument.h \
    connections/clsConnection.h \
    connections/clsLan.h \
    connections/clsLcrConnection.h \
    connections/clsLcrCnntWindow.h \
    PublicFiles/clsSettings.h \
    connections/clsHVConnection.h \
    connections/clsHVCnntWindow.h \
    connections/clsFtdiConnection.h \
    connections/clsFtdiCnntWindow.h \
    connections/clsTestClass.h \
    connections/clsFtdiOperation.h \
    UiFiles/QFlowLayout.h \
    UiFiles/clsMainTestWindow.h \
    UiFiles/clsWarningBox.h \
    UiFiles/clsSelectUpdateStep.h \
    Instruments/clsWK6500RunningMode.h \
    Instruments/clsHVRunningMode.h \
    Instruments/clsRunningMeterFactory.h \
    UiFiles/clsTestConditon.h \
    UiFiles/clsMeterUnit.h \
    UiFiles/dlgLevelInputBox.h \
    UiFiles/clsSignalDisplayWidget.h \
    PublicFiles/clsDataStatistics.h \
    Ftdi/clsSelectFtdiChip.h \
    MulitChannel/clsCalibration.h \
    MulitChannel/ClickedLabel.h \
    MulitChannel/clsCalibrationDbOp.h \
    MulitChannel/clsDataProcess.h \
    MulitChannel/clsStandardValueInput.h \
    PublicFiles/clsComplexOp.h \
    PublicFiles/complexType.h \
    MulitChannel/MessageDialog.h \
    MulitChannel/clsInstrumentCalibration.h \
    PublicFiles/clsGlobleVarient.h \
    Qextserial/qextserialport.h \
    Qextserial/qextserialport_global.h \
    Qextserial/qextserialport_p.h \
    MulitChannel/clsWK6500CalibrationMeter.h \
    MulitChannel/clsSingleTrig.h \
    MulitChannel/clsSampleTest.h \
    Service/clsRunService.h \
    Service/singleton.h \
    UiFiles/clsRunningSettings.h \
    Service/clsRunSettings.h \
    UiFiles/frmSelectLang.h \
    connections/clsConnectToServer.h

SOURCES += \
    PublicFiles/clsMeterLimit.cpp \
    PublicFiles/doubleType.cpp \
    PublicFiles/main.cpp \
    UiFiles/clsChannelSettings.cpp \
    UiFiles/clsHightVoltage.cpp \
    UiFiles/clsLabel.cpp \
    UiFiles/clsNewSetup.cpp \
    UiFiles/clsRangeDialog.cpp \
    UiFiles/clsSpeedDialog.cpp \
    UiFiles/clsWK6500Items.cpp \
    UiFiles/clsWK6500Meter.cpp \
    UiFiles/frmSetLimit.cpp \
    UiFiles/NumberInput.cpp \
    PublicFiles/publicUtility.cpp \
    UiFiles/clsHVChannelSettings.cpp \
    UiFiles/clsMeterFactory.cpp \
    UiFiles/clsMeter.cpp \
    Service/clsSignalStatus.cpp \
    Service/clsRunService.cpp \
    connections/clsConnection.cpp \
    connections/clsLan.cpp \
    connections/clsLcrConnection.cpp \
    connections/clsLcrCnntWindow.cpp \
    PublicFiles/clsSettings.cpp \
    connections/clsHVConnection.cpp \
    connections/clsHVCnntWindow.cpp \
    connections/clsFtdiConnection.cpp \
    connections/clsFtdiCnntWindow.cpp \
    connections/clsTestClass.cpp \
    connections/clsFtdiOperation.cpp \
    UiFiles/QFlowLayout.cpp \
    UiFiles/clsMainTestWindow.cpp \
    UiFiles/clsWarningBox.cpp \
    UiFiles/clsSelectUpdateStep.cpp \
    Instruments/clsWK6500RunningMode.cpp \
    Instruments/clsHVRunningMode.cpp \
    UiFiles/clsMeterUnit.cpp \
    UiFiles/dlgLevelInputBox.cpp \
    UiFiles/clsSignalDisplayWidget.cpp \
    PublicFiles/clsDataStatistics.cpp \
    Ftdi/clsSelectFtdiChip.cpp \
    MulitChannel/clsCalibration.cpp \
    MulitChannel/ClickedLabel.cpp \
    MulitChannel/clsCalibrationDbOp.cpp \
    MulitChannel/clsDataProcess.cpp \
    MulitChannel/clsStandardValueInput.cpp \
    PublicFiles/clsComplexOp.cpp \
    PublicFiles/complexType.cpp \
    MulitChannel/MessageDialog.cpp \
    MulitChannel/clsInstrumentCalibration.cpp \
    PublicFiles/clsGlobleVarient.cpp \
    Qextserial/qextserialport.cpp \
    Qextserial/qextserialport_win.cpp \
    MulitChannel/clsWK6500CalibrationMeter.cpp \
    MulitChannel/clsSingleTrig.cpp \
    MulitChannel/clsSampleTest.cpp \
    UiFiles/clsRunningSettings.cpp \
    Service/clsRunSettings.cpp \
    UiFiles/frmSelectLang.cpp \
    connections/clsConnectToServer.cpp

FORMS += \
    UiFiles/clsHightVoltage.ui \
    UiFiles/clsNewSetup.ui \
    UiFiles/clsRangeDialog.ui \
    UiFiles/clsSpeedDialog.ui \
    UiFiles/clsWK6500Items.ui \
    UiFiles/clsWK6500Meter.ui \
    UiFiles/frmSetLimit.ui \
    UiFiles/NumberInput.ui \
    UiFiles/clsHVChannelSettings.ui \
    connections/clsLcrCnntWindow.ui \
    connections/clsHVCnntWindow.ui \
    connections/clsFtdiCnntWindow.ui \
    UiFiles/clsMainTestWindow.ui \
    UiFiles/clsWarningBox.ui \
    UiFiles/clsSelectUpdateStep.ui \
    UiFiles/clsMeterUnit.ui \
    UiFiles/dlgLevelInputBox.ui \
    UiFiles/clsSignalDisplayWidget.ui \
    Ftdi/clsSelectFtdiChip.ui \
    MulitChannel/clsCalibration.ui \
    MulitChannel/clsStandardValueInput.ui \
    MulitChannel/MessageDialog.ui \
    MulitChannel/clsSampleTest.ui \
    UiFiles/clsRunningSettings.ui \
    UiFiles/clsMeterChannelSettings.ui \
    UiFiles/clsRunningStatus.ui \
    UiFiles/frmSelectLang.ui

DISTFILES += \
    Describle.txt

RC_FILE  =Icon.rc

win32: LIBS += -L$$PWD/NLogger/ -lNLogger

INCLUDEPATH += $$PWD/NLogger/include
DEPENDPATH += $$PWD/NLogger

TRANSLATIONS = images\Translation/WKEFV_EN.ts \
               images\Translation/WKEFV_Zh.ts \
               images\Translation/WKEFV_Tw.ts \
               images\Translation/WKEFV_GM.ts \
               images\Translation/WKEFV_JP.ts
