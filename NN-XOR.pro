QT += core
QT -= gui

TARGET = NN-XOR
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    neuron.cpp

HEADERS += \
    neuron.h

