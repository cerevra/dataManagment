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
    calcalg.cpp

HEADERS  += mainwindow.h \
    calcalg.h \
    iplugin.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x


DIR = $$_PRO_FILE_PWD_/../bin

#target_dll.path =

CONFIG(debug, debug|release)  {
    DIR = $$DIR/debug

}
else: {
    DIR = $$DIR/release
}

DESTDIR += $$DIR
