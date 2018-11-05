#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T12:25:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ADORM
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    loaddata.cpp \
    graph.cpp \
    loading.cpp \
    personinfo.cpp \
    chart.cpp \
    statistics.cpp \
    chineseletterhelper.cpp \
    softinfo.cpp \
    personcenter.cpp

HEADERS  += widget.h \
    loaddata.h \
    graph.h \
    loading.h \
    personinfo.h \
    chart.h \
    statistics.h \
    chineseletterhelper.h \
    softinfo.h \
    personcenter.h

FORMS    += widget.ui \
    loaddata.ui \
    loading.ui \
    personinfo.ui \
    chart.ui \
    searchlevel.ui \
    statistics.ui \
    softinfo.ui \
    personcenter.ui

RESOURCES += \
    src.qrc
