#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T13:45:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku_shfGroup
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tableio.cpp \
    data.cpp \
    aboutdialog.cpp \
    helpdialog.cpp \
    timer.cpp

HEADERS  += mainwindow.h \
    tableio.h \
    data.h \
    aboutdialog.h \
    helpdialog.h \
    timer.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    helpdialog.ui

RESOURCES += \
    res.qrc


DISTFILES += \
    suduku.rc

RC_FILE = \
    suduku.rc
