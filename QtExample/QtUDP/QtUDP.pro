#-------------------------------------------------
#
# Project created by QtCreator 2016-01-26T18:44:58
#
#-------------------------------------------------

QT       += core gui
QT		 += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtUDP
TEMPLATE = app


SOURCES += main.cpp\
        udpserver.cpp

HEADERS  += udpserver.h
