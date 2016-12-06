#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T12:28:53
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpleTextureMapping
TEMPLATE = app

INCLUDEPATH *= /usr/local/include
LIBS *= -lQGLViewer -lGLU

SOURCES += main.cpp\
        mainwindow.cpp \
    viewerwidget.cpp

HEADERS  += mainwindow.h \
    viewerwidget.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -c -Wall -Wno-write-strings -Wno-sign-compare -Wno-unused-result -fPIC -O0 -std=c++11
