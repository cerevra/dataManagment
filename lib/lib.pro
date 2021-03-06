#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T09:54:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataManagement
TEMPLATE = lib

CONFIG += staticlib
CONFIG -= dll

SOURCES += ../host/calcalg.cpp

HEADERS += ../host/calcalg.h \
           ../host/iplugin.h

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../host

DIR = $$_PRO_FILE_PWD_/../lib
CONFIG(debug, debug|release)  {
    DIR = $$DIR/debug
}
else: {
    DIR = $$DIR/release
}
DIR ~= s,/,\\,g

DESTDIR += $$DIR

exists($$DIR): {}
else: QMAKE_PRE_LINK  += mkdir \"$$DIR\" & if not exist \"$$DIR\" exit 1
