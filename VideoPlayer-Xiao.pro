#-------------------------------------------------
#
# Project created by QtCreator 2018-03-22T13:59:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPlayer-Xiao
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    videoplayer.cpp \
    cqopengldisplay.cpp \
    cffmpeg.cpp

HEADERS += \
    mainwindow.h \
    videoplayer.h \
    cqopengldisplay.h \
    cffmpeg.h

FORMS += \
    mainwindow.ui




FFMPEF_PATH  = $$PWD/../../ffmpeg
INCLUDEPATH += $$FFMPEF_PATH/include
LIBS        += $$FFMPEF_PATH/lib/avcodec.lib   \
               $$FFMPEF_PATH/lib/avdevice.lib  \
               $$FFMPEF_PATH/lib/avfilter.lib  \
               $$FFMPEF_PATH/lib/avformat.lib  \
               $$FFMPEF_PATH/lib/avutil.lib    \
               $$FFMPEF_PATH/lib/postproc.lib  \
               $$FFMPEF_PATH/lib/swresample.lib  \
               $$FFMPEF_PATH/lib/swscale.lib  \
