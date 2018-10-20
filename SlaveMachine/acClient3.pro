#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T13:43:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network
TARGET = acClient3
TEMPLATE = app


SOURCES += main.cpp\
        loginview.cpp \
    loginmodel.cpp \
    socketsingle.cpp \
    mainview.cpp \
    mainmodel.cpp \
    room.cpp

HEADERS  += loginview.h \
    loginmodel.h \
    socketsingle.h \
    mainview.h \
    mainmodel.h \
    room.h

FORMS    += loginview.ui \
    mainview.ui
