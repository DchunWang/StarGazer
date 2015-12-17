#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T14:53:46
#
#-------------------------------------------------

QT       += core gui
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myWord
TEMPLATE = app


SOURCES += main.cpp\
        myword.cpp \
    centralwidget.cpp

HEADERS  += myword.h \
    centralwidget.h
