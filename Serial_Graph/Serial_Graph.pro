#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T16:06:23
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Serial_Graph
TEMPLATE = app


SOURCES += main.cpp\
           serialgraph.cpp \
           qcustomplot.cpp \
           serialtool.cpp

HEADERS  += serialgraph.h \
            qcustomplot.h \
            serialtool.h

FORMS    += serialgraph.ui \
            serialtool.ui
