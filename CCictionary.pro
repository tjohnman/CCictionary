#-------------------------------------------------
#
# Project created by QtCreator 2014-04-04T13:46:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CCictionary
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogloading.cpp \
    dialogloadingworker.cpp \
    datamodel.cpp \
    term.cpp \
    searchworker.cpp

HEADERS  += mainwindow.h \
    dialogloading.h \
    dialogloadingworker.h \
    datamodel.h \
    term.h \
    searchworker.h

FORMS    += mainwindow.ui \
    dialogloading.ui
