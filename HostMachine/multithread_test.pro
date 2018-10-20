#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T21:52:52
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multithread_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    multithread_server.cpp \
    multithread.cpp \
    client.cpp \
    database.cpp \
    fifo.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    multithread_server.h \
    multithread.h \
    client.h \
    database.h \
    fifo.h \
    form.h

FORMS    += mainwindow.ui \
    form.ui

RESOURCES += \
    picture.qrc
