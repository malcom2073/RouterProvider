#-------------------------------------------------
#
# Project created by QtCreator 2017-05-30T21:58:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRouterCoreProvider
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cbor.cpp

HEADERS  += mainwindow.h \
    cbor.h

FORMS    += mainwindow.ui
