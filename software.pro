#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T09:58:47
#
#-------------------------------------------------

QT += core gui

QMAKE_CXXFLAGS += -std=gnu++11 -Wall -Wextra

unix:LIBS += -lmatio -larmadillo

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = software
TEMPLATE = app


SOURCES += main.cpp\
        plotwindow.cpp \
    plot.cpp \
    dialog.cpp

HEADERS  += plotwindow.h \
    structs.h \
    plot.h \
    dialog.h

FORMS    += plotwindow.ui \
    dialog.ui

CONFIG += mobility
MOBILITY = 

DISTFILES +=

RESOURCES += \
    images.qrc
