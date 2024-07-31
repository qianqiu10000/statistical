QT       += core widgets

TEMPLATE=app
TARGET=statistical

CONFIG += c++11

SOURCES+= main.cpp \
    myAnalyzer.cpp \
    myFindFiles.cpp

RC_ICONS=ICON.ico

HEADERS += \
    myAnalyzer.h \
    myFindFiles.h

QMAKE_CXXFLAGS+=/utf-8

