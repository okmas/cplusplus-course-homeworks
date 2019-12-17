TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    bitcoin.cpp

HEADERS += \
    bitcoin.h

QMAKE_CFLAGS += -ansi -pedantic -Wall -Wextra
