#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T01:13:11
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = FeatureEx
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /home/hagar13/opencv-3.0.0/build/opencv2

LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_nonfree
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann


SOURCES += main.cpp
