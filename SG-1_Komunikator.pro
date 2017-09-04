#-------------------------------------------------
#
# Project created by QtCreator 2017-09-04T12:44:11
#
#-------------------------------------------------

QT			+= core gui
QT			+= serialport

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SG-1_Komunikator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtrswrapper.cpp \
    sg1frame.cpp

HEADERS  += mainwindow.h \
    qtrswrapper.h \
    sg1frame.h

FORMS    += mainwindow.ui
