QT += core
QT -= gui

CONFIG += c++11

TARGET = Projeto_Final
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    projeto.cpp

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH +=C:\OpenCV320\include

LIBS += -LC:\OpenCV320\x86\mingw\bin \
    libopencv_core320 \
    libopencv_highgui320 \
    libopencv_imgcodecs320 \
    libopencv_imgproc320 \
    libopencv_features2d320 \
    libopencv_calib3d320 \
    libopencv_videoio320

HEADERS += \
    projeto.h
