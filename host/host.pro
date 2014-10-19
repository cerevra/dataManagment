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
    plugins.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    calcalg.h \
    iplugin.h \
    plugins.h \
    about.h

FORMS    += mainwindow.ui \
    plugins.ui \
    about.ui

QMAKE_CXXFLAGS += -std=c++0x


#target_dll.path =

DIR = $$_PRO_FILE_PWD_/../bin
CONFIG(debug, debug|release)  {
    DIR = $$DIR/debug
}
else: {
    DIR = $$DIR/release
}
DIR ~= s,/,\\,g

DESTDIR += $$DIR

QMAKE_PRE_LINK  += if not exist $$DIR mkdir $$DIR & if not exist $$DIR exit 1
