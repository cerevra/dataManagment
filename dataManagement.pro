#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T09:54:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataManagement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calcalg.cpp \
    calcuniform.cpp

HEADERS  += mainwindow.h \
    calcalg.h \
    calcuniform.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
