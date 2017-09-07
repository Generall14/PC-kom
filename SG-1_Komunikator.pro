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
    src/Factory.cpp \
    src/Frame.cpp \
    src/Frame_imp/FrameEmpty.cpp \
    src/MediumUI.cpp \
    src/MediumUI_imp/MediumUIEmpty.cpp \
    src/MediumUI_imp/MediumUIRS.cpp \
    src/Mendium.cpp \
    src/Mendium_imp/MendiumRS.cpp \
    src/Mendium_imp/MendiumEmpty.cpp \
    src/Frame_imp/FrameTransparent.cpp \
    src/LogicUI.cpp \
    src/LogicUI_imp/LogicUIEmpty.cpp \
    src/FrameBuilder.cpp \
    src/FrameBuilder_imp/FrameBuilderEmpty.cpp \
    src/LogUI.cpp \
    src/LogUI_imp/LogUIEmpty.cpp

HEADERS  += mainwindow.h \
    src/Factory.hpp \
    src/Frame.hpp \
    src/Frame_imp/FrameEmpty.hpp \
    src/MediumUI.hpp \
    src/MediumUI_imp/MediumUIEmpty.hpp \
    src/MediumUI_imp/MediumUIRS.hpp \
    src/Mendium.hpp \
    src/Mendium_imp/MendiumRS.hpp \
    src/Mendium_imp/MendiumEmpty.hpp \
    src/Frame_imp/FrameTransparent.hpp \
    src/LogicUI.hpp \
    src/LogicUI_imp/LogicUIEmpty.hpp \
    src/FrameBuilder.hpp \
    src/FrameBuilder_imp/FrameBuilderEmpty.hpp \
    src/LogUI.hpp \
    src/LogUI_imp/LogUIEmpty.hpp

FORMS    += mainwindow.ui
