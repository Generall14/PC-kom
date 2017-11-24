#-------------------------------------------------
#
# Project created by QtCreator 2017-09-04T12:44:11
#
#-------------------------------------------------

QT			+= core gui
QT			+= serialport

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PC-Kom
TEMPLATE = app

GIT_VERSION = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"


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
    src/LogicUI_imp/utils/Worker.cpp \
    src/LogicUI_imp/utils/WorkerManager.cpp \
    src/LogicUI_imp/utils_SG1/DataCollector.cpp \
    src/Mendium_imp/MendiumFakeStawrow.cpp \
    src/Frame_imp/FrameStawrov.cpp \
    src/FrameBuilder_imp/FrameBuilderStawrov.cpp \
    src/LogicUI_imp/LogicUIStawrov.cpp \
    src/LogFile_imp/LogFileEmpty.cpp \
    src/LogFile_imp/LogFileDefault.cpp \
    src/LogFormater_imp/LogFormaterEmpty.cpp \
    src/LogFormater_imp/LogFormaterHtml.cpp \
    src/Frame_imp/FrameZR3.cpp \
    src/FrameBuilder_imp/FrameBuilderZR3.cpp \
    src/LogicUI_imp/LogicUIZR3.cpp \
    src/Utils/Desc.cpp \
    src/Utils/About.cpp \
    src/Mendium_imp/MendiumBusConnector.cpp \
    src/BusDevice_imp/BusDeviceUMP.cpp \
    src/LogicUI_imp/utils_ZR3/ZR3UIFrame.cpp \
    src/LogicUI_imp/utils_ZR3/ZR3ReadFile.cpp \
    src/LogicUI_imp/utils_Stawrov/StawrovLogger.cpp \
    src/Utils/ValidateHex.cpp \
    src/Utils/ValidateDumbFloat.cpp \
    src/Utils/Restorable.cpp \
    src/LogicUI_imp/utils_ZR3/ZR3UIFrameUI.cpp \
    src/LogicUI_imp/utils_ZR3/transactionDesc.cpp \
    src/LogicUI_imp/utils_ZR3/ParamUi.cpp \
    src/LogicUI_imp/utils_ZR3/transactionUi.cpp

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
    src/LogicUI_imp/utils/Transaction.hpp \
    src/LogicUI_imp/utils/Worker.hpp \
    src/LogicUI_imp/utils/WorkerManager.hpp \
    src/LogicUI_imp/utils_SG1/DataCollector.hpp \
    init.hpp \
    src/Mendium_imp/MendiumFakeStawrow.hpp \
    src/Frame_imp/FrameStawrov.hpp \
    src/FrameBuilder_imp/FrameBuilderStawrov.hpp \
    src/LogicUI_imp/LogicUIStawrov.hpp \
    devices.hpp \
    src/LogFile.hpp \
    src/LogFile_imp/LogFileEmpty.hpp \
    src/LogFile_imp/LogFileDefault.hpp \
    src/LogFormater.hpp \
    src/LogFormater_imp/LogFormaterEmpty.hpp \
    src/LogFormater_imp/LogFormaterHtml.hpp \
    src/Frame_imp/FrameZR3.hpp \
    src/FrameBuilder_imp/FrameBuilderZR3.hpp \
    src/LogicUI_imp/LogicUIZR3.hpp \
    src/Utils/Desc.hpp \
    src/Utils/About.hpp \
    src/Mendium_imp/MendiumBusConnector.hpp \
    src/BusDevice.hpp \
    src/BusDevice_imp/BusDeviceUMP.hpp \
    src/LogicUI_imp/utils_ZR3/ZR3UIFrame.hpp \
    src/LogicUI_imp/utils_ZR3/ZR3ReadFile.hpp \
    src/LogicUI_imp/utils_Stawrov/StawrovLogger.hpp \
    src/Utils/ValidateHex.hpp \
    src/Utils/ValidateDumbFloat.hpp \
    src/Utils/Restorable.hpp \
    src/LogicUI_imp/utils_ZR3/ZR3UIFrameUI.hpp \
	src/LogicUI_imp/utils_ZR3/devClass.hpp \
    src/LogicUI_imp/utils_ZR3/method.hpp \
    src/LogicUI_imp/utils_ZR3/param.hpp \
    src/LogicUI_imp/utils_ZR3/transactionDesc.hpp \
    src/LogicUI_imp/utils_ZR3/ParamUi.hpp \
    src/LogicUI_imp/utils_ZR3/transactionUi.hpp
