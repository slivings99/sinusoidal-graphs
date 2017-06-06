#-------------------------------------------------
#
# Project created by QtCreator 2017-06-01T11:54:17
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SinusoidalGraphs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    creategraphswindow.cpp \
    pinumber.cpp \
    renderarea.cpp \
    pinumbertest.cpp

HEADERS  += mainwindow.h \
    creategraphswindow.h \
    pinumber.h \
    renderarea.h \
    pinumbertest.h

FORMS    += mainwindow.ui \
    creategraphswindow.ui
