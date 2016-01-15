#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T23:36:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

//添加QtPrintSupport模块支持
qtHaveModule(printsupport): QT += printsupport

TARGET = QtWord
TEMPLATE = app


SOURCES += main.cpp\
        qtword.cpp \
    mychild.cpp

HEADERS  += qtword.h \
    mychild.h

RESOURCES += \
    qtword.qrc
