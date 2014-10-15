#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T22:54:24
#
#-------------------------------------------------

QT       -= gui

TARGET = calcUniform
TEMPLATE = lib

SOURCES += calcuniform.cpp \
    calcplugin.cpp

HEADERS += calcuniform.h \
    calcplugin.h

INCLUDEPATH += ../manager

QMAKE_CXXFLAGS += -std=c++0x

LIBPATH = $$_PRO_FILE_PWD_/../lib

LIBS += -L$$LIBPATH -ldataManagement

DDIR = $$_PRO_FILE_PWD_\..\bin
CONFIG(debug, debug|release)  {
    DDIR = $$DDIR\debug
}
else: {
    DDIR = $$DDIR\release
}
DDIR = $$DDIR\plugins
win: DDIR ~= s,/,\\,g

DESTDIR += $$DDIR

QMAKE_POST_LINK += $$QMAKE_DEL_FILE $$DDIR\\libcalcUniform.a
