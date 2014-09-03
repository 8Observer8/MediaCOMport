#-------------------------------------------------
#
# Project created by QtCreator 2014-09-02T10:00:42
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MediaCOMport
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Receiver.cpp \
    SettingsDialog.cpp

HEADERS  += MainWindow.h \
    PortError.h \
    Receiver.h \
    SettingsDialog.h

FORMS    += MainWindow.ui \
    SettingsDialog.ui

RESOURCES += \
    resource.qrc
