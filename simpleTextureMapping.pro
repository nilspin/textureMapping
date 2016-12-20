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
    viewerwidget.cpp \
    imgui/imgui.cpp \
    imgui/imgui_draw.cpp \
    imgui/imgui_demo.cpp \
    imgui/imgui_impl_qt.cpp

HEADERS  += mainwindow.h \
    viewerwidget.h \
    imgui/imgui.h \
    imgui/stb_truetype.h \
    imgui/stb_textedit.h \
    imgui/stb_rect_pack.h \
    imgui/imgui_internal.h \
    imgui/imgui_impl_qt.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -c -Wall -Wno-write-strings -Wno-sign-compare -Wno-unused-result -fPIC -O0 -std=c++11
