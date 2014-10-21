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

INCLUDEPATH += ../../host

QMAKE_CXXFLAGS += -std=c++0x

LIBPATH = $$_PRO_FILE_PWD_/../../lib

DIR = $$_PRO_FILE_PWD_/../../bin
win: DIR ~= s,/,\\,g

QMAKE_PRE_LINK = echo

exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\"

CONFIG(debug, debug|release)  {
    DIR     = $$DIR/debug
    LIBPATH = $$LIBPATH/debug
}
else: {
    DIR = $$DIR/release
    LIBPATH = $$LIBPATH/release
}
win: DIR ~= s,/,\\,g

exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\"

DIR = $$DIR/plugins
win: DIR ~= s,/,\\,g
win: LIBPATH ~= s,/,\\,g

LIBS += -L$$LIBPATH -ldataManagement
DESTDIR += $$DIR

exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\" & if not exist \"$$DIR\" exit 1

DELS = $$DIR\\*.a
DELS ~= s,/,\\,g
QMAKE_POST_LINK += $$QMAKE_DEL_FILE $$DELS
