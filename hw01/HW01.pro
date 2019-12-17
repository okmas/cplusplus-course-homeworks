TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -ansi -pedantic -Wall -Wextra

SOURCES += main.cpp \
    card.cpp \
    land.cpp \
    creature.cpp \
    player.cpp

HEADERS += \
    card.h \
    land.h \
    creature.h \
    player.h

