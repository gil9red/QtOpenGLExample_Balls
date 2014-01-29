QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app

DESTDIR = ../bin

SOURCES += main.cpp \
    UScene3D.cpp

HEADERS  += \
    UScene3D.h
