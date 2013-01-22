#-------------------------------------------------
#
# Project created by QtCreator 2012-12-06T16:12:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MM
TEMPLATE = app

SOURCES += main.cpp\
        friendlist.cpp \
    dialog.cpp \
    server.cpp \
    cthread.cpp

HEADERS  += friendlist.h \
    dialog.h \
    server.h \
    cthread.h

FORMS    += friendlist.ui \
    dialog.ui

OTHER_FILES +=

RESOURCES += \
    ico.qrc
