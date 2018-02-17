TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS +=     \
    catch.hpp

INCLUDEPATH += \
    ../PC-kom/src/

SOURCES += \
    main.cpp \
    example.cpp
