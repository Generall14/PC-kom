#-------------------------------------------------
#
# Project created by QtCreator 2017-09-04T12:44:11
#
#-------------------------------------------------

QT			+= core gui
QT			+= serialport

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PC-Kom
TEMPLATE = app

GIT_VERSION = $$system(git --git-dir $$PWD/../.git --work-tree $$PWD describe --always --tags)
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

INCLUDEPATH += \
    ./src/

LIBS += -lpugixml

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
    src/FrameBuilder_imp/FrameBuilderEmpty.cpp \
    src/LogUI.cpp \
    src/LogUI_imp/LogUIEmpty.cpp \
    src/LogUI_imp/LogUITerm.cpp \
    src/LogicUI_imp/LogicUISG-1.cpp \
    src/Utils/EQThread.cpp \
    src/Frame_imp/FrameSG1.cpp \
    src/FrameBuilder_imp/FrameBuilderSG1.cpp \
    src/Mendium_imp/MendiumFakeSG1.cpp \
    src/LogicUI_imp/utils_SG1/DataCollector.cpp \
    src/Mendium_imp/MendiumFakeStawrow.cpp \
    src/Frame_imp/FrameStawrov.cpp \
    src/FrameBuilder_imp/FrameBuilderStawrov.cpp \
    src/LogicUI_imp/LogicUIStawrov.cpp \
    src/LogFile_imp/LogFileEmpty.cpp \
    src/LogFile_imp/LogFileDefault.cpp \
    src/LogFormater_imp/LogFormaterEmpty.cpp \
    src/LogFormater_imp/LogFormaterHtml.cpp \
    src/Utils/Desc.cpp \
    src/Utils/About.cpp \
    src/LogicUI_imp/utils_Stawrov/StawrovLogger.cpp \
    src/Utils/ValidateHex.cpp \
    src/Utils/ValidateDumbFloat.cpp \
    src/Utils/Restorable.cpp \
    src/Utils/StaticUtils.cpp \
    src/LogicUI_imp/utils_SG1/Worker.cpp \
    src/LogicUI_imp/utils_SG1/WorkerManager.cpp \
    src/LogicUI_imp/utils_SG1/WorkerRead.cpp \
    src/LogicUI_imp/utils_SG1/WorkerWrite.cpp \
    src/LogicUI_imp/LogicUITerminal.cpp \
    src/FrameBuilder_imp/FrameBuilderTerminal.cpp \
    src/LogicUI_imp/utils_Terminal/Terminal_SendSection.cpp \
    src/Utils/CRC.cpp \
    src/Mendium_imp/MendiumEcho.cpp \
    src/Utils/HexItemDelegate.cpp \
    src/Utils/GlobalXmlFile.cpp \
    src/LogicUI_imp/utils_Stawrov/KontrolerPomiarowy.cpp \
    src/Utils/DisplayMes.cpp \
    src/Utils/PazurCRC.cpp \
    src/LogicUI_imp/LogicUISProt.cpp \
    src/LogicUI_imp/utils_SProt/SProtPure.cpp

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
    src/LogUI_imp/LogUIEmpty.hpp \
    src/LogUI_imp/LogUITerm.hpp \
    src/LogicUI_imp/LogicUISG-1.hpp \
    src/Utils/EQThread.hpp \
    src/Frame_imp/FrameSG1.hpp \
    src/FrameBuilder_imp/FrameBuilderSG1.hpp \
    src/Mendium_imp/MendiumFakeSG1.hpp \
    src/LogicUI_imp/utils_SG1/DataCollector.hpp \
    src/Mendium_imp/MendiumFakeStawrow.hpp \
    src/Frame_imp/FrameStawrov.hpp \
    src/FrameBuilder_imp/FrameBuilderStawrov.hpp \
    src/LogicUI_imp/LogicUIStawrov.hpp \
    src/LogFile.hpp \
    src/LogFile_imp/LogFileEmpty.hpp \
    src/LogFile_imp/LogFileDefault.hpp \
    src/LogFormater.hpp \
    src/LogFormater_imp/LogFormaterEmpty.hpp \
    src/LogFormater_imp/LogFormaterHtml.hpp \
    src/Utils/Desc.hpp \
    src/Utils/About.hpp \
    src/LogicUI_imp/utils_Stawrov/StawrovLogger.hpp \
    src/Utils/ValidateHex.hpp \
    src/Utils/ValidateDumbFloat.hpp \
    src/Utils/Restorable.hpp \
    src/Utils/StaticUtils.hpp \
    src/LogicUI_imp/utils_SG1/Worker.hpp \
    src/LogicUI_imp/utils_SG1/WorkerManager.hpp \
    src/LogicUI_imp/utils_SG1/WorkerRead.hpp \
    src/LogicUI_imp/utils_SG1/WorkerWrite.hpp \
    src/LogicUI_imp/LogicUITerminal.hpp \
    src/FrameBuilder_imp/FrameBuilderTerminal.hpp \
    src/LogicUI_imp/utils_Terminal/Terminal_SendSection.hpp \
    src/Utils/CRC.hpp \
    src/Mendium_imp/MendiumEcho.hpp \
    src/Utils/HexItemDelegate.hpp \
    src/Utils/GlobalXmlFile.hpp \
    src/LogicUI_imp/utils_Stawrov/KontrolerPomiarowy.hpp \
    src/Utils/DisplayMes.hpp \
    src/Utils/PazurCRC.hpp \
    src/LogicUI_imp/LogicUISProt.hpp \
    src/LogicUI_imp/utils_SProt/SProtPure.hpp

DISTFILES += \
    configs.xml \
    set.cfg

