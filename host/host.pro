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


# Deploying

DIR = $$_PRO_FILE_PWD_/../bin

QMAKE_PRE_LINK = echo
exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\"

CONFIG(debug, debug|release)  {
    DIR = $$DIR/debug
}
else: {
    DIR = $$DIR/release
}

exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\"

DESTDIR += $$DIR

DLLS = $$system(copy.bat)

DLLS_tmp += Qt5Core \
            Qt5Gui \
            Qt5Widgets

DLL_PLATFORM_tmp = qminimal \
                   qoffscreen \
                   qwindows

CONFIG(release, debug|release)  {
    for (d, DLLS_tmp): {
        DLLS += $${d}.dll
    }

    for (d, DLL_PLATFORM_tmp): {
        DLL_PLATFORM += $${d}.dll
    }
}
else: {
    for (d, DLLS_tmp): {
        DLLS += $${d}d.dll
    }

    for (d, DLL_PLATFORM_tmp): {
        DLL_PLATFORM += $${d}d.dll
    }
}

QMAKE_POST_LINK = echo
for (d, DLLS): {
QMAKE_POST_LINK += & copy /y \"$(QT_DIR)\bin\\$${d}\" \"$$DIR\\$${d}\"
}

DIR = $$DIR/platforms
exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\" & if not exist \"$$DIR\" exit 1

for (d, DLL_PLATFORM): {
QMAKE_POST_LINK += & copy /y \"$(QT_DIR)\plugins\\platforms\\$${d}\" \"$$DIR\\$${d}\"
}
