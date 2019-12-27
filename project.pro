QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    askwindow.cpp \
    helpwindow.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    mainwindow.h \
    askwindow.h \
    helpwindow.h
