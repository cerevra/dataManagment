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

SOURCES += ../manager/calcalg.cpp

HEADERS += calcalg.h \
    iplugin.h

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../manager

DESTDIR += $$_PRO_FILE_PWD_/../lib
