#-------------------------------------------------
#
# Project created by QtCreator 2017-05-30T21:58:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRouterCoreProvider
TEMPLATE = app
include (../QRouterLib/qrouterlib.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    cbor.cpp \
    gpssimprovider.cpp \
    obdsimprovider.cpp

HEADERS  += mainwindow.h \
    cbor.h \
    gpssimprovider.h \
    obdsimprovider.h

FORMS    += mainwindow.ui \
    gpssimprovider.ui \
    obdsimprovider.ui
