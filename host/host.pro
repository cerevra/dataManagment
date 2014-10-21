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
win: DIR ~= s,/,\\,g

QMAKE_PRE_LINK = echo
exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\"

CONFIG(debug, debug|release)  {
    DIR = $$DIR/debug
}
else: {
    DIR = $$DIR/release
}
win: DIR ~= s,/,\\,g

exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\"

DESTDIR += $$DIR

DLLS = icudt52 \
    icuin52 \
    icuuc52 \
    libgcc_s_dw2-1 \
    libstdc++-6 \
    libwinpthread-1

CONFIG(release, debug|release)  {
    DLLS += Qt5Core \
            Qt5Gui \
            Qt5Widgets

    DLL_PLATFORM = qminimal \
                   qoffscreen \
                   qwindows
}
else: {
    DLLS += Qt5Cored \
            Qt5Guid \
            Qt5Widgetsd

    DLL_PLATFORM = qminimald \
                   qoffscreend \
                   qwindowsd
}

QMAKE_POST_LINK = echo
for (d, DLLS): {
QMAKE_POST_LINK += & copy /y \"$(QT_DIR)\bin\\$${d}.dll\" \"$$DIR\\$${d}.dll\"
}

DIR = $$DIR/platforms
win: DIR ~= s,/,\\,g
exists($$DIR): {}
else: QMAKE_PRE_LINK  += & mkdir \"$$DIR\" & if not exist \"$$DIR\" exit 1

for (d, DLL_PLATFORM): {
QMAKE_POST_LINK += & copy /y \"$(QT_DIR)\plugins\\platforms\\$${d}.dll\" \"$$DIR\\$${d}.dll\"
}
