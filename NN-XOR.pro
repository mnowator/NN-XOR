QT += core xml
QT -= gui

TARGET = NN-XOR
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    neuron.cpp \
    neuronslayer.cpp \
    neuralnetwork.cpp

HEADERS += \
    neuron.h \
    neuronslayer.h \
    neuralnetwork.h \

