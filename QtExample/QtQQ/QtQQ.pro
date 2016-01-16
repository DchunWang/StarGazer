#-------------------------------------------------
#
# Project created by QtCreator 2016-01-16T11:11:11
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtQQ
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    drawer.cpp \
    server.cpp \
    client.cpp

HEADERS  += widget.h \
    drawer.h \
    server.h \
    client.h

RESOURCES += \
    qtqq.qrc

FORMS += \
    widget.ui \
    server.ui \
    client.ui
